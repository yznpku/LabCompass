import os
import subprocess
import zipfile

subprocess.run(['pyinstaller', 'package.spec'], input=b'y')
os.chdir('dist')
with zipfile.ZipFile('LabCompass.zip', 'w', zipfile.ZIP_DEFLATED) as zipf:
  for root, dirs, files in os.walk('LabCompass/'):
    for file in files:
      zipf.write(os.path.join(root, file))
