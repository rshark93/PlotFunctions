set(MAIN_TARGET_NAME ${PROJECT_NAME}Main)
set(srcPath ../src/)
set(incPath ../headers/)

add_executable( ${MAIN_TARGET_NAME} 
    "main.cpp" "main.h"
)

#set(MATPLOT_LIBS ../../../matplotplusplus/lib)
set(MATPLOT_LIBS ../../../matplotplusplus/lib)

#set(MATPLOT_LIBRARIES ${MATPLOT_LIBS}/matplot)
set(MATPLOT_LIBRARIES ${MATPLOT_LIBS}/Matplot++/nodesoup ${MATPLOT_LIBS}/matplot)

find_file(MATPLOT_INCLUDE_DIRS NAME matplot/matplot.h HINTS matplot)
find_library(MATPLOT_LIB NAME matplot)

target_include_directories(${MAIN_TARGET_NAME} PRIVATE ${MATPLOT_INCLUDE_DIRS})

target_link_libraries(${MAIN_TARGET_NAME} ${MATPLOT_LIBRARIES})