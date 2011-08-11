# Component: neatogen
#####################################################
# Description:
# ------------
#	 Cmake Input File for neatogen
#####################################################

project( neatogen )

set (	SRCS
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/adjust.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/bfs.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/call_tri.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/circuit.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/closest.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/compute_hierarchy.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/conjgrad.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/constrained_majorization.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/constraint.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/delaunay.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/dijkstra.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/edges.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/embed_graph.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/find_ints.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/geometry.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/heap.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/hedges.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/info.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/intersect.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/kkutils.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/legal.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/lu.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/matinv.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/matrix_ops.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/memory.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/multispline.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/neatoinit.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/neatosplines.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/opt_arrangement.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/overlap.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/pca.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/poly.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/printvis.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/quad_prog_solve.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/site.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/smart_ini_x.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/solve.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/stress.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/stuff.c
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen/voronoi.c
	)

include_directories (
	${EXTERNALS_DIRECTORY}/graphviz2/lib/neatogen
	${EXTERNALS_DIRECTORY}/graphviz2/lib/common
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cgraph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pack
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gvc
	${EXTERNALS_DIRECTORY}/graphviz2/lib/gd
	${EXTERNALS_DIRECTORY}/graphviz2/lib/cdt
	${EXTERNALS_DIRECTORY}/graphviz2/lib/graph
	${EXTERNALS_DIRECTORY}/graphviz2/lib/pathplan
	${EXTERNALS_DIRECTORY}/graphviz2/lib/sparse
	${EXTERNALS_DIRECTORY}/graphviz2
	)

if (WIN32)
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE -DMSWIN32 )
else ()
	ADD_DEFINITIONS( -DHAVE_CONFIG_H -DHAVE_SETMODE )
endif ()

add_library ( neatogen STATIC
			${SRCS}
			)
target_link_libraries ( neatogen
						common
						pathplan
						pack
	)


