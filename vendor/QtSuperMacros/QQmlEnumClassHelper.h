#ifndef QQMLENUMCLASS
#define QQMLENUMCLASS

#include <QObject>
#include <QString>
#include <QQmlEngine>
#include <QMetaEnum>
#include <QMetaObject>
#include <qqml.h>

#ifdef Q_ENUM
#   define QML_EXPORT_ENUM Q_ENUM
#else
#   define QML_EXPORT_ENUM Q_ENUMS
#endif

#define QML_ENUM_CLASS(NAME, ...) \
    struct NAME { \
        Q_GADGET \
        public: \
            enum Type { \
                __VA_ARGS__ \
            }; \
            QML_EXPORT_ENUM (Type) \
            static QString asString (const int value) { \
                return QString::fromLatin1 (staticMetaObject.enumerator (0).valueToKey (value)); \
            } \
            static void registerQmlModule (const char * uri, const int majorVersion, const int minorVersion, const char * name) { \
                qmlRegisterUncreatableType<NAME> (uri, majorVersion, minorVersion, name, "Enum class, can't be instanciated !"); \
            } \
        private: \
            explicit NAME (void) { } \
            NAME (const NAME &); \
            NAME & operator= (const NAME &); \
    }; \
    Q_DECLARE_METATYPE (NAME::Type)

QML_ENUM_CLASS (_Test_QmlEnumClass_) // NOTE : to avoid "no suitable class found" MOC note

#endif // QQMLENUMCLASS

