# Component: neatogen
#####################################################
# Description:
# ------------
#	 Cmake Input File for neatogen
#####################################################

project( neatogen )

set (	SRCS
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/adjust.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/bfs.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/call_tri.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/circuit.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/closest.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/compute_hierarchy.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/conjgrad.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/constrained_majorization.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/constraint.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/delaunay.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/dijkstra.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/edges.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/embed_graph.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/find_ints.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/geometry.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/heap.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/hedges.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/info.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/intersect.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/kkutils.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/legal.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/lu.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/matinv.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/matrix_ops.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/memory.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/multispline.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/neatoinit.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/neatosplines.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/opt_arrangement.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/overlap.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/pca.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/poly.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/printvis.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/quad_prog_solve.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/site.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/smart_ini_x.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/solve.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/stress.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/stuff.c
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen/voronoi.c
	)

include_directories (
	${GRAPHVIZ_INCLUDE_DIRS}/lib/neatogen
	${GRAPHVIZ_INCLUDE_DIRS}/lib/common
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cgraph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pack
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gvc
	${GRAPHVIZ_INCLUDE_DIRS}/lib/gd
	${GRAPHVIZ_INCLUDE_DIRS}/lib/cdt
	${GRAPHVIZ_INCLUDE_DIRS}/lib/graph
	${GRAPHVIZ_INCLUDE_DIRS}/lib/pathplan
	${GRAPHVIZ_INCLUDE_DIRS}/lib/sparse
	${GRAPHVIZ_INCLUDE_DIRS}
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


