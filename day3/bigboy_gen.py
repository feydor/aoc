import sys
import os
import numpy as np
def sample(width, max_lines):
  last_int = (2**width)
  outputs = []
  if last_int > max_lines:
    keepratio = max_lines/(last_int)
    print("Keepratio:", keepratio)
    print("Aiming for {} lines".format(int(keepratio*last_int)))
  else:
    keepratio = 1.0
  print("Generating... ", end='')
  for i in range(0,last_int):
    if i%100000 == 0:
        print("\rGenerating... {:8.7f}% (done: {})".format(i/last_int, len(outputs)), end='')
    if np.random.random() > keepratio:
        continue
    b = bin(i)[2:].rjust(width, '0')
    outputs.append(b)
  print('')
  return outputs

def gen(width, max_lines, max_attempts):
  ok = set()
  print("Generating (either to max attempts or enough are found)...")
  for i in range(max_attempts):
    print(f"\rAttempts: {i/max_attempts:8.7f}%\tFound: {len(ok)/max_lines:8.7f}%", end='')
    choice = np.random.choice(["0","1"], width, replace=True)
    b = "".join(choice)
    ok.add(b)
    if len(ok) >= max_lines:
        break
  return list(ok)
def main(width, shuffle=True, max_lines=950250):
  """
    warning: Setting max_lines too low might result in a column of only 1s or only 0s
             this might break some implementations. With a high max_lines, it is very
             improbably to get an entire column like this.
  """
  output_file = 'bigboi_generated.txt'

  if width >= 26:
    outputs = gen(width=width, max_lines=max_lines, max_attempts=max_lines*2)
  else:
    outputs = sample(width, max_lines)

  if len(outputs)%2 == 0:
    outputs.pop()

  print("Generated {} lines".format(len(outputs)))
  print("Writing to {}".format(output_file))
  with open(output_file, 'w') as f:
    for o in outputs:
        f.write(o + '\n')

if __name__ == '__main__':
  np.random.seed(1)
  if len(sys.argv) > 1:
    width = int(sys.argv[1])
  else:
    width = 60
  main(width)
