#include "precompiled_headers.h"

#include "FontResolver.h"

namespace hpcc
{
#if defined FB_WIN
#define DEFAULT_FONTPATH "C:/WINDOWS/FONTS;C:/WINNT/Fonts;C:/winnt/fonts"
#define DEFAULT_FONT "ArialUni;Arial;Verdana"
#elif defined FB_X11
/* default fontpath for unix systems  - whatever happened to standards ! */
#define DEFAULT_FONTPATH "/usr/X11R6/lib/X11/fonts;/usr/share/fonts;/usr/openwin/lib/X11/fonts;/usr/lib/X11/fonts"
#define DEFAULT_FONT "wqy-zenhei;DejaVu Sans;DejaVuSans;Liberation Sans;FreeSans;Verdana"
#elif defined FB_MACOSX	
#define DEFAULT_FONTPATH "/Library/Fonts;/System/Library/Fonts"
#define DEFAULT_FONT "Hei;LucidaGrande;DejaVu Sans;DejaVuSans;Liberation Sans;FreeSans;Verdana"
#endif

typedef std::vector<std::string> split_vector_type;
struct ciLessBoost : std::binary_function<std::string, std::string, bool> 
{ 
    bool operator() (const std::string & s1, const std::string & s2) const { 
        return boost::lexicographical_compare(s1, s2, boost::is_iless()); 
    } 
}; 
typedef std::map<std::string, std::string, ciLessBoost> StringStringMap;

//  ===========================================================================
class CFontResolver : public IFontResolver, public CUnknown
{
protected:
	FT_Library m_ftLibrary;   
	bool m_ftLibraryLoaded;

	StringStringMap m_stemPath;
	StringStringMap m_familynamePath;
	std::string m_defaultPath;

public:
	BEGIN_CUNKNOWN
	END_CUNKNOWN

	CFontResolver()
	{
		m_ftLibraryLoaded = false;
		FT_Error error = FT_Init_FreeType(&m_ftLibrary);
		if (!error)
			m_ftLibraryLoaded = true;

		split_vector_type searchFolders; 
		boost::algorithm::split(searchFolders, DEFAULT_FONTPATH, boost::algorithm::is_any_of(";"), boost::algorithm::token_compress_on);

		for(split_vector_type::const_iterator itr = searchFolders.begin(); itr != searchFolders.end(); ++itr) {
			findFilesByExt(*itr, ".ttf", m_stemPath);
			findFilesByExt(*itr, ".ttc", m_stemPath);
		}

		split_vector_type defaultFonts; 
		boost::algorithm::split(defaultFonts, DEFAULT_FONT, boost::algorithm::is_any_of(";"), boost::algorithm::token_compress_on);

		for(split_vector_type::const_iterator itr = defaultFonts.begin(); itr != defaultFonts.end(); ++itr) 
		{
			StringStringMap::const_iterator found = m_stemPath.find(*itr);
			if (found != m_stemPath.end())
			{
				m_defaultPath = found->second;
				break;
			}
		}

		if (m_defaultPath.empty())
		{
#if defined WIN32
			m_defaultPath = "c:/windows/fonts/verdana.ttf";
#else
			m_defaultPath = "/usr/share/fonts/truetype/freefont/FreeSans.ttf";
#endif
		}
	}

	~CFontResolver()
	{
		if (m_ftLibraryLoaded)
		{
			FT_Done_FreeType(m_ftLibrary);
			m_ftLibraryLoaded = false;
		}
	}

	const char * GetPath(const std::string & _label)
	{
		split_vector_type labels; 
		boost::algorithm::split(labels, _label, boost::algorithm::is_any_of(","), boost::algorithm::token_compress_on);
		for(split_vector_type::const_iterator itr = labels.begin(); itr != labels.end(); ++itr)
		{
			StringStringMap::const_iterator found = m_familynamePath.find(*itr);
			if (found != m_familynamePath.end())
				return found->second.c_str();

			found = m_stemPath.find(*itr);
			if (found != m_stemPath.end())
				return found->second.c_str();
		}

		return GetDefaultPath();
	}

	const char * GetDefaultPath()
	{
		return m_defaultPath.c_str();
	}

	double GetDefaultSize()
	{
		return 14.0f;
	}

protected:
	void findFilesByExt(const boost::filesystem::path & folder, const std::string & ext, StringStringMap & found)
	{
		if (boost::filesystem::is_directory(folder))
		{
			for(boost::filesystem::directory_iterator itr(folder); itr != boost::filesystem::directory_iterator(); ++itr)
			{
				if (boost::algorithm::iequals(boost::filesystem::extension(*itr), ext))
				{
					found[itr->path().stem().string()] = itr->path().string();
					getFamilyName(itr->path().string());
				}

				findFilesByExt(*itr, ext, found);
			}
		}
	}

	void getFamilyName(const std::string & fontPath)
	{
		FT_Face face;      /* handle to face object */
		FT_Error error = FT_New_Face(m_ftLibrary, fontPath.c_str(), 0, &face);
		if ( error == FT_Err_Unknown_File_Format )
		{
			/*
		... the font file could be opened and read, but it appears
		... that its font format is unsupported
			*/
		}
		else if (error)
		{
			/*
		... another error code means that the font file could not
		... be opened or read, or simply that it is broken...
			*/
		}
		else
		{
			if (!face->style_flags)
				m_familynamePath[face->family_name] = fontPath;
			FT_Done_Face(face);
		}
	}

};

IFontResolverPtr g_fontResolver;
boost::recursive_mutex g_FontResolver;

IFontResolver * CreateIFontResolver()
{
	boost::recursive_mutex::scoped_lock lock(g_FontResolver);
	if (!g_fontResolver)
		g_fontResolver = new CFontResolver();
	return g_fontResolver;
}

}