import subprocess
from time import sleep
import shutil
import os
from pathlib import Path

# INPUTS ==============================
populate = True
test = True
remove = True
# INPUTS ==============================

all_match = False
if populate:
  result = subprocess.run(['./main.exe'], capture_output=True, text=True)
  if result.returncode == 0:
      print("Success!")
      print(result.stdout)
  else:
      print("Error!")
      print(result.stderr)

sleep(.25)

for i in range(1,7):
  if os.path.exists(f'{i}_test-e.txt'):
    shutil.move(f'{i}_test-e.txt', 'test')
  else:
    print(f"File {i}_test-e.txt not found")
  if os.path.exists(f'{i}_test-r.txt'):
     shutil.move(f'{i}_test-r.txt', 'test')
  else:
    print(f"File {i}_test-r.txt not found")

sleep(.25)

if test:
  for i in range(1,13):
    base_path = Path("C:/Users/hconn/OneDrive/Desktop/BAE RESOURCES/phys engine/test/")

    if i < 7:
      test_file = base_path / f"{i}_test-e.txt"
      answer_file = base_path / f"{i}_euler.txt" 
    else:
      test_file = base_path / f"{i-6}_test-r.txt"
      answer_file = base_path / f"{i-6}_rk.txt" 

    test_content = test_file.read_text() 
    answer_content = answer_file.read_text()
    
    if test_content == answer_content:
      print(f"Case {i}: MATCH")
    else:
      all_match = False
      print(f"Case {i}: MISMATCH")
      all_match = False
        # Find first differing line
      for idx, (test_line, ans_line) in enumerate(zip(test_content, answer_content)):
        if test_line != ans_line:
          print(f"  First mismatch  at line {idx+1}:")
          print(f"    Test:   {test_line.rstrip()}")
          print(f"    Answer: {ans_line.rstrip()}")
          break
      else:
          # If all lines matched but lengths differ
        if len(test_content) != len(answer_content):
          print(f"  File length mismatch: test has {len(test_content)} lines, answer has {len(answer_content)} lines")

sleep(.25)
if remove:
  for i in range(1,13):
    path = "C:/Users/hconn/OneDrive/Desktop/BAE RESOURCES/phys engine/test/"
    if i < 7:
      filename = f"{i}_test-e.txt"
    else:
      filename = f"{i-6}_test-r.txt"

    delete = os.path.join(path, filename)
    if os.path.exists:
        os.remove(delete)
        print(f"deleted: {filename}")

if all_match:
  print("\n ALL TEST CASES PASS")
else:
  print("\n one or more test cases failed")