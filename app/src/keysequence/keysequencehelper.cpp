#include "keysequencehelper.h"

uint qHash(const QKeySequence &seq)
{
    return qHash(seq.toString());
}

class KeySequenceHelperPrivate
{
public:
    KeySequenceHelperPrivate(KeySequenceHelper *q);

    void init();

    static QKeySequence appendToSequence(const QKeySequence &seq, int keyQt);
    static bool isOkWhenModifierless(int keyQt);

    void updateShortcutDisplay();
    void startRecording();

    bool checkAgainstStandardShortcuts() const
    {
        return checkAgainstShortcutTypes & KeySequenceHelper::StandardShortcuts;
    }

    bool checkAgainstGlobalShortcuts() const
    {
        return checkAgainstShortcutTypes & KeySequenceHelper::GlobalShortcuts;
    }

    void controlModifierlessTimout()
    {
        if (nKey != 0 && !modifierKeys) {
            // No modifier key pressed currently. Start the timout
            modifierlessTimeout.start(600);
        } else {
            // A modifier is pressed. Stop the timeout
            modifierlessTimeout.stop();
        }

    }

    void cancelRecording()
    {
        keySequence = oldKeySequence;
        q->doneRecording();
    }


//members
    KeySequenceHelper *const q;
    QToolButton *clearButton;

    QKeySequence keySequence;
    QKeySequence oldKeySequence;
    QTimer modifierlessTimeout;
    bool allowModifierless;
    uint nKey;
    uint modifierKeys;
    bool isRecording;
    bool multiKeyShortcutsAllowed;
    QString componentName;
    QString shortcutDisplay;

    //! Check the key sequence against KStandardShortcut::find()
    KeySequenceHelper::ShortcutTypes checkAgainstShortcutTypes;

    /**
     * The list of action to check against for conflict shortcut
     */
    QList<QAction *> checkList; // deprecated

    /**
     * The list of action collections to check against for conflict shortcut
     */
//     QList<KActionCollection *> checkActionCollections;

    /**
     * The action to steal the shortcut from.
     */
    QList<QAction *> stealActions;
};

KeySequenceHelperPrivate::KeySequenceHelperPrivate(KeySequenceHelper *q)
: q(q)
, allowModifierless(false)
, nKey(0)
, modifierKeys(0)
, isRecording(false)
, multiKeyShortcutsAllowed(true)
, componentName()
, checkAgainstShortcutTypes(KeySequenceHelper::StandardShortcuts | KeySequenceHelper::GlobalShortcuts)
, stealActions()
{

}

KeySequenceHelper::KeySequenceHelper(QObject* parent):
    QObject(),
    d(new KeySequenceHelperPrivate(this))
{
    Q_UNUSED(parent);
    connect(&d->modifierlessTimeout, SIGNAL(timeout()), this, SLOT(doneRecording()));
    d->updateShortcutDisplay();
}


KeySequenceHelper::~KeySequenceHelper()
{
    delete d;
}

bool KeySequenceHelper::multiKeyShortcutsAllowed() const
{
    return d->multiKeyShortcutsAllowed;
}

void KeySequenceHelper::setMultiKeyShortcutsAllowed(bool allowed)
{
    d->multiKeyShortcutsAllowed = allowed;
}

void KeySequenceHelper::setModifierlessAllowed(bool allow)
{
    d->allowModifierless = allow;
}

bool KeySequenceHelper::isModifierlessAllowed()
{
    return d->allowModifierless;
}

bool KeySequenceHelper::isKeySequenceAvailable(const QKeySequence& keySequence) const
{
  return true;
}

//
// void KeySequenceHelper::setCheckActionCollections(const QList<KActionCollection *> &actionCollections)
// {
//     d->checkActionCollections = actionCollections;
// }
//

//slot
void KeySequenceHelper::captureKeySequence()
{
    d->startRecording();
}

QKeySequence KeySequenceHelper::keySequence() const
{
    return d->keySequence;
}

void KeySequenceHelper::setKeySequence(const QKeySequence& sequence)
{
    if (!d->isRecording) {
        d->oldKeySequence = d->keySequence;
    }
    d->keySequence = sequence;
    d->updateShortcutDisplay();
    emit keySequenceChanged(d->keySequence);
}


void KeySequenceHelper::clearKeySequence()
{
    setKeySequence(QKeySequence());
}

void KeySequenceHelperPrivate::startRecording()
{
    nKey = 0;
    modifierKeys = 0;
    oldKeySequence = keySequence;
    keySequence = QKeySequence();
    isRecording = true;

    updateShortcutDisplay();
}
//

void KeySequenceHelper::cancelRecording() {
  d->keySequence = d->oldKeySequence;
  d->modifierlessTimeout.stop();
  d->isRecording = false;
  d->stealActions.clear();
  d->updateShortcutDisplay();
}
void KeySequenceHelper::doneRecording()
{
    d->modifierlessTimeout.stop();
    d->isRecording = false;
    d->stealActions.clear();

    if (d->keySequence == d->oldKeySequence) {
//         The sequence hasn't changed
        d->updateShortcutDisplay();
        return;
    }

    if (! isKeySequenceAvailable(d->keySequence)) {
//         The sequence had conflicts and the user said no to stealing it
        d->keySequence = d->oldKeySequence;
    } else {
        emit keySequenceChanged(d->keySequence);
    }

    Q_EMIT captureFinished();

    d->updateShortcutDisplay();
}

void KeySequenceHelperPrivate::updateShortcutDisplay()
{
    //empty string if no non-modifier was pressed
    QString s = keySequence.toString(QKeySequence::NativeText);
    s.replace(QLatin1Char('&'), QStringLiteral("&&"));

    if (isRecording) {
        if (modifierKeys) {
            if (!s.isEmpty()) {
                s.append(QLatin1Char(','));
            }
            if (modifierKeys & Qt::META) {
                s += "Meta" + QLatin1Char('+');
            }
#if defined(Q_OS_MAC)
            if (modifierKeys & Qt::ALT) {
                s += "Alt" + QLatin1Char('+');
            }
            if (modifierKeys & Qt::CTRL) {
                s += "Ctrl" + QLatin1Char('+');
            }
#else
            if (modifierKeys & Qt::CTRL) {
                s += "Ctrl" + QLatin1Char('+');
            }
            if (modifierKeys & Qt::ALT) {
                s += "Alt" + QLatin1Char('+');
            }
#endif
            if (modifierKeys & Qt::SHIFT) {
                s += "Shift" + QLatin1Char('+');
            }

        } else if (nKey == 0) {
            s = "Press Keys";
        }
        //make it clear that input is still going on
        s.append(QStringLiteral(" ..."));
    }

    if (s.isEmpty()) {
        s = "Not Set";
    }

    s.prepend(QLatin1Char(' '));
    s.append(QLatin1Char(' '));
    shortcutDisplay = s;
    q->shortcutDisplayChanged(s);
}

QString KeySequenceHelper::shortcutDisplay() const
{
    return d->shortcutDisplay;
}

void KeySequenceHelper::keyPressed(int key, int modifiers)
{
    if (key == -1) {
        return d->cancelRecording();
    }

    //don't have the return or space key appear as first key of the sequence when they
    //were pressed to start editing - catch and them and imitate their effect
    if (!d->isRecording && ((key == Qt::Key_Return || key == Qt::Key_Space))) {
        d->startRecording();
        d->modifierKeys = modifiers;
        d->updateShortcutDisplay();
        return;
    }

    d->modifierKeys = modifiers;

    switch (key) {
    case Qt::Key_AltGr: //or else we get unicode salad
        return;
    case Qt::Key_Shift:
    case Qt::Key_Control:
    case Qt::Key_Alt:
    case Qt::Key_Meta:
    case Qt::Key_Super_L:
    case Qt::Key_Super_R:
    case Qt::Key_Menu: //unused (yes, but why?)
        d->controlModifierlessTimout();
        d->updateShortcutDisplay();
        break;
    default:

        if (d->nKey == 0 && !(d->modifierKeys & ~Qt::SHIFT)) {
            // It's the first key and no modifier pressed. Check if this is
            // allowed
            if (!(KeySequenceHelperPrivate::isOkWhenModifierless(key)
                    || d->allowModifierless)) {
                // No it's not
                return;
            }
        }

        // We now have a valid key press.
        if (key) {
            if ((key == Qt::Key_Backtab) && (d->modifierKeys & Qt::SHIFT)) {
                key = Qt::Key_Tab | d->modifierKeys;
            } else {
                key |= (d->modifierKeys);
            }

            if (d->nKey == 0) {
                d->keySequence = QKeySequence(key);
            } else {
                d->keySequence =
                    KeySequenceHelperPrivate::appendToSequence(d->keySequence, key);
            }

            d->nKey++;
            if ((!d->multiKeyShortcutsAllowed) || (d->nKey >= 4)) {
                doneRecording();
                return;
            }
            d->controlModifierlessTimout();
            d->updateShortcutDisplay();
        }
    }
}
//
void KeySequenceHelper::keyReleased(int key, int modifiers)
{
    if (key == -1) {
        // ignore garbage, see keyPressEvent()
        return;
    }

    //if a modifier that belongs to the shortcut was released...
    if ((modifiers & d->modifierKeys) < d->modifierKeys) {
        d->modifierKeys = modifiers;
        d->controlModifierlessTimout();
        d->updateShortcutDisplay();
    }
}
//
//static
QKeySequence KeySequenceHelperPrivate::appendToSequence(const QKeySequence &seq, int keyQt)
{
    if (seq.matches(keyQt) != QKeySequence::NoMatch) {
        return seq;
    }

    switch (seq.count()) {
    case 0:
        return QKeySequence(keyQt);
    case 1:
        return QKeySequence(seq[0], keyQt);
    case 2:
        return QKeySequence(seq[0], seq[1], keyQt);
    case 3:
        return QKeySequence(seq[0], seq[1], seq[2], keyQt);
    default:
        return seq;
    }
}
//
//static
bool KeySequenceHelperPrivate::isOkWhenModifierless(int keyQt)
{
    //this whole function is a hack, but especially the first line of code
    if (QKeySequence(keyQt).toString().length() == 1) {
        return false;
    }

    switch (keyQt) {
    case Qt::Key_Return:
    case Qt::Key_Space:
    case Qt::Key_Tab:
    case Qt::Key_Backtab: //does this ever happen?
    case Qt::Key_Backspace:
    case Qt::Key_Delete:
        return false;
    default:
        return true;
    }
}
