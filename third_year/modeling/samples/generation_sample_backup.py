import simpy
import random

class Generator:

    def __init__(self):
        pass
    
    def generate(self, quantity, low_bound, high_bound):
        env = simpy.Environment()
        env.process(self.write_random_numbers(env, low_bound, high_bound))
        env.run(until=quantity)
        return self.numbers

    def write_random_numbers(self, env, low_bound, high_bound):
        self.numbers = []
        while True:
            value = int(random.random()*(high_bound - low_bound) + low_bound)
            self.numbers.append(value)
            yield env.timeout(1)

if __name__ == "__main__":
    quantity_of_columns = 5
    quantity_of_numbers = 20000
    low_bound = 10
    high_bound = 19
    
    generator = Generator()
    numbers = generator.generate(quantity_of_numbers, low_bound, high_bound)
    numbers_per_column = int((high_bound - low_bound + 1)/quantity_of_columns)
    start_value = low_bound
    statistics = [[],[]]
    for i in range(1, quantity_of_columns):
        statistics[0].append([start_value, start_value + numbers_per_column - 1])
        statistics[1].append(0)
        start_value += numbers_per_column
        
    statistics[0].append([start_value, high_bound])
    statistics[1].append(0)

    for i in range(len(numbers)):
        for j in range(len(statistics[0])):
            if numbers[i] >= statistics[0][j][0] and \
               numbers[i] <= statistics[0][j][1]:
                statistics[1][j] += 1
        
    print(statistics)
    
