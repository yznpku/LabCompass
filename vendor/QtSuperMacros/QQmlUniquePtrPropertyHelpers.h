#ifndef QQMLUNIQUEPTRPROPERTYHELPERS_H
#define QQMLUNIQUEPTRPROPERTYHELPERS_H

#include <QObject>

#include <memory>
#include "QQmlHelpersCommon.h"

#define QML_READONLY_UNIQUEPTR_PROPERTY(type, name) \
    protected: \
        Q_PROPERTY (type * name READ MAKE_GETTER_NAME (name) NOTIFY name##Changed) \
    private: \
        std::unique_ptr<type> m_##name; \
    public: \
        type * MAKE_GETTER_NAME (name) (void) const { \
            return m_##name.get(); \
        } \
    public Q_SLOTS: \
        bool update_##name (type * name) { \
            bool ret = false; \
            if ((ret = (m_##name.get() != name))) { \
                m_##name.reset(name); \
                emit name##Changed (m_##name.get()); \
            } \
            return ret; \
        } \
        bool update_##name (std::unique_ptr<type> & name) { \
            bool ret = false; \
            if ((ret = (m_##name.get() != name.get()))) { \
                m_##name = std::move(name); \
                emit name##Changed (m_##name.get()); \
            } \
            return ret; \
        } \
    Q_SIGNALS: \
        void name##Changed (type * name); \
    private:



#endif // QQMLUNIQUEPTRPROPERTYHELPERS_H
