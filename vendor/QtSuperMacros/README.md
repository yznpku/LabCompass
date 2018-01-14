Qt Super-Macros
===============

A set of one-line C++ macros to simplify the creation of reccurent things (like Qt Meta Properties) so that doing them in C++ is not harder than in QML, and requires no boilerplate glue-code.

## For one-line creation of QML properties

* `QML_WRITABLE_***_PROPERTY` : a macro that takes a type and a name, and creates automatically the member attribute, the public getter and setter, and the Qt signal for notifier, and allow use in QML by exposing a read/write `Q_PROPERTY`.

* `QML_READONLY_***_PROPERTY` : another macro that does almost the same as `QML_WRITABLE_PROPERTY` except that the property is not modifiable from the QML side, only C++ can access the setter.

* `QML_CONSTANT_***_PROPERTY` : a simplified version of the previous macros, that exposes a constant property with no getter and no setter, from C++ or QML side.

The `***` can be either `VAR`, `PTR`, `CSTREF`, or `AUTO`. The three first are simple macros that you use by simply passing the non-qualified type (`T`) and it'll add the qualifiers for var (none), pointer (`*`), or constant-reference (`const &`) where needed. The last one in the other hand, uses either `T` or `T*` and it's capable of adding constant-reference by deciding itself which type is the cheapest (using some template trickery internally).

> INFO : by default, getters are named `get_<property name>`, but if you want more Qt-compliant naming (no prefix) you can set the `QTQMLTRICKS_NO_PREFIX_ON_GETTERS` flag in QMake or QBS.


## For easier QQmlListProperty from QList

* `QML_LIST_PROPERTY` : a really handy macro to create a QML list property that maps to an internal `QList` of objects, without having to declare and implement all static function pointers...


## For simple enum class that can be used in C++ and QML

* `QML_ENUM_CLASS` : a macro to declare a `QObject` class that only contains a `Q_ENUM` and can be exposed as is to QML.


> NOTE : If you want to donate, use this link : [![Flattr this](http://api.flattr.com/button/flattr-badge-large.png)](https://flattr.com/submit/auto?user_id=thebootroo&url=http://gitlab.unique-conception.org/qt-qml-tricks/qt-supermacros)
