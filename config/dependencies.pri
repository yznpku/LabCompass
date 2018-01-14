win32-msvc*: LIBSUFFIX = lib
else: LIBSUFFIX = a

for(dep, DEPEND_LIBS) {
    LIBS += -L../$${dep}/ -l$${dep}
    PRE_TARGETDEPS += ../$${dep}/lib$${dep}.$${LIBSUFFIX}
}

for(dep, DEPEND_VENDOR_LIBS) {
    LIBS += -L../vendor/$${dep}/ -l$${dep}
    PRE_TARGETDEPS += ../vendor/$${dep}/lib$${dep}.$${LIBSUFFIX}
}
