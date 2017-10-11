import json

class Options(dict):
  def __init__(self):
    super().__init__({
      'difficulty': 'Uber',
      'mainWindowPosition': [100, 100],
      'poeClientPath': ''
    })
    try:
      with open('options.json') as file:
        self.update(json.loads(file.read()))
    except:
      pass

  def saveToFile(self):
    with open('options.json', 'w') as file:
      file.write(json.dumps(self))
