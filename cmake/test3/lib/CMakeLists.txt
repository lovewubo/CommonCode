SET(LIBHELLO_SRC hello.c)
ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
#ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})
#SET_TARGET_PROPERTiES(hello_static PROPERTIES OUTPUT_NAME "hello")
SET_TARGET_PROPERTiES(hello PROPERTIES VERSION 1.2 SOVERSION 1)
INSTALL(TARGETS hello LIBRARY DESTINATION lib)
INSTALL(FILES hello.h DESTINATION include/hello)
