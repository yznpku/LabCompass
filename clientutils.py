import os.path
import psutil
import win32gui
import win32process

def getClientPath():
  hwnd = win32gui.FindWindow('POEWindowClass', None)
  if hwnd:
    _, pid = win32process.GetWindowThreadProcessId(hwnd)
    try:
      return os.path.dirname(psutil.Process(pid).exe())
    except Exception:
      return ''
  else:
    return ''

def verifyClientPath(path):
  return os.path.exists(path + '/logs/Client.txt')
