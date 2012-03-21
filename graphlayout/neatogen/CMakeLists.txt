# Component: neatogen
#####################################################
# Description:
# ------------
#	 Cmake Input File for neatogen
#####################################################

project( neatogen )

set (	SRCS
	${GRAPHVIZSRC_DIRS}/lib/neatogen/adjust.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/bfs.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/call_tri.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/circuit.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/closest.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/compute_hierarchy.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/conjgrad.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/constrained_majorization.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/constrained_majorization_ipsep.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/constraint.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/delaunay.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/dijkstra.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/edges.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/embed_graph.c
	#${GRAPHVIZSRC_DIRS}/lib/neatogen/find_ints.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/geometry.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/heap.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/hedges.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/info.c
	#${GRAPHVIZSRC_DIRS}/lib/neatogen/intersect.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/kkutils.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/legal.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/lu.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/matinv.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/matrix_ops.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/memory.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/multispline.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/neatoinit.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/neatosplines.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/opt_arrangement.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/overlap.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/pca.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/poly.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/printvis.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/quad_prog_solve.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/site.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/smart_ini_x.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/solve.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/stress.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/stuff.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/voronoi.c
	${GRAPHVIZSRC_DIRS}/lib/neatogen/quad_prog_vpsc.c
	)

include_directories (
	${GRAPHVIZSRC_DIRS}/lib/neatogen
	${GRAPHVIZSRC_DIRS}/lib/common
	${GRAPHVIZSRC_DIRS}/lib/cgraph
	${GRAPHVIZSRC_DIRS}/lib/pack
	${GRAPHVIZSRC_DIRS}/lib/gvc
	${GRAPHVIZSRC_DIRS}/lib/gd
	${GRAPHVIZSRC_DIRS}/lib/cdt
	${GRAPHVIZSRC_DIRS}/lib/graph
	${GRAPHVIZSRC_DIRS}/lib/pathplan
	${GRAPHVIZSRC_DIRS}/lib/sparse
	${GRAPHVIZSRC_DIRS}/lib/vpsc
	${GRAPHVIZSRC_DIRS}/lib/ortho
	${GRAPHVIZSRC_DIRS}
	..
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


