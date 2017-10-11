def connect(d):
  for signal in d:
    for slot in d[signal]:
      signal.connect(slot)
