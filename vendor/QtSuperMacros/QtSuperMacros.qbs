import qbs;

Project {
    name: "Qt super-macros";

    Product {
        name: "libqtqmltricks-qtsupermacros";
        type: "staticlibrary";
        targetName: "QtSuperMacros";

        Export {
            cpp.includePaths: ".";

            Depends { name: "cpp"; }
            Depends {
                name: "Qt";
                submodules: ["core", "qml"];
            }
        }
        Depends { name: "cpp"; }
        Depends {
            name: "Qt";
                submodules: ["core", "qml"];
        }
        Group {
            name: "C++ sources";
            files: [
                "QQmlHelpers.cpp",
            ]
        }
        Group {
            name: "C++ headers";
            files: [
                "QQmlConstRefPropertyHelpers.h",
                "QQmlEnumClassHelper.h",
                "QQmlListPropertyHelper.h",
                "QQmlPtrPropertyHelpers.h",
                "QQmlSingletonHelper.h",
                "QQmlVarPropertyHelpers.h",
            ]
        }
        Group {
            qbs.install: (product.type === "dynamiclibrary");
            fileTagsFilter: product.type;
        }
    }
}
