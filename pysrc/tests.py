from imp import NullImporter
import math
from scipy.special import expit
import matplotlib.pyplot as plt

def formula(x: int) -> float:

    return 1/x

def sigmoid(x: float):
  return 1 / (1 + math.exp(-x))

def generate_list() -> list[float]:
    numbers: list[float] = []

    for n in range(-50, 50):
        numbers.append(expit(n / 10.0))
    return numbers

    min_hold_time = 1300
    hold_time = 50000
    time = 1

    while hold_time > min_hold_time:
        # hold_time = hold_time - .5
        hold_time = hold_time - hold_time/1
        time += 1
        numbers.append(hold_time)
    return numbers


def main():
    numbers = generate_list()
    strs = [str(n) for n in numbers]
    print("\n".join(strs))
    fig = plt.figure()
    fig.canvas.mpl_connect('key_press_event', lambda event: plt.close(fig) if event.key == 'q' else None)
    plt.plot(numbers)
    plt.show()




if __name__ == "__main__":
    main()
