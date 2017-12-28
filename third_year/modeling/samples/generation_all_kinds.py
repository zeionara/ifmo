import simpy
import random
import xlrd, xlwt
import xlsxwriter

class Generator:

    def __init__(self):
        pass

    def generate_statistics(self, quantity_of_columns, quantity_of_numbers, low_bound, high_bound):
        self.generate(quantity_of_numbers, low_bound, high_bound)
        numbers_per_column = int((high_bound - low_bound + 1)/quantity_of_columns)
        start_value = low_bound
        statistics = [[],[]]
        for i in range(1, quantity_of_columns):
            statistics[0].append([start_value, start_value + numbers_per_column - 1])
            statistics[1].append(0)
            start_value += numbers_per_column
        
        statistics[0].append([start_value, high_bound])
        statistics[1].append(0)

        for i in range(len(self.numbers)):
            for j in range(len(statistics[0])):
                if self.numbers[i] >= statistics[0][j][0] and \
                   self.numbers[i] <= statistics[0][j][1]:
                    statistics[1][j] += 1

        return statistics

    def generate_statistics_exp(self, quantity_of_columns, quantity_of_numbers, low_bound, high_bound, lambd):
        self.generate_exp(quantity_of_numbers, low_bound, high_bound, lambd)
        numbers_per_column = int((high_bound - low_bound + 1)/quantity_of_columns)
        start_value = low_bound
        statistics = [[],[]]
        for i in range(1, quantity_of_columns):
            statistics[0].append([start_value, start_value + numbers_per_column - 1])
            statistics[1].append(0)
            start_value += numbers_per_column
        
        statistics[0].append([start_value, high_bound])
        statistics[1].append(0)

        for i in range(len(self.numbers)):
            for j in range(len(statistics[0])):
                if (self.numbers[i] >= statistics[0][j][0] and \
                   self.numbers[i] <= statistics[0][j][1]) or (self.numbers[i] >= statistics[0][j][0] and\
                   j == len(statistics[0]) - 1):
                    statistics[1][j] += 1

        return statistics

    def generate_statistics_erl(self, quantity_of_columns, quantity_of_numbers, low_bound, high_bound, lambd, order):
        self.generate_erl(quantity_of_numbers, low_bound, high_bound, lambd, order)
        numbers_per_column = int((high_bound - low_bound + 1)/quantity_of_columns)
        start_value = low_bound
        statistics = [[],[]]
        for i in range(1, quantity_of_columns):
            statistics[0].append([start_value, start_value + numbers_per_column - 1])
            statistics[1].append(0)
            start_value += numbers_per_column
        
        statistics[0].append([start_value, high_bound])
        statistics[1].append(0)

        for i in range(len(self.numbers)):
            for j in range(len(statistics[0])):
                if (self.numbers[i] >= statistics[0][j][0] and \
                   self.numbers[i] <= statistics[0][j][1]) or (self.numbers[i] >= statistics[0][j][0] and\
                   j == len(statistics[0]) - 1):
                    statistics[1][j] += 1

        return statistics
    
    def generate(self, quantity, low_bound, high_bound):
        env = simpy.Environment()
        env.process(self.write_random_numbers(env, low_bound, high_bound))
        env.run(until=quantity)
        return self.numbers

    def generate_exp(self, quantity, low_bound, high_bound, lambd):
        env = simpy.Environment()
        env.process(self.write_random_numbers_exp(env, low_bound, high_bound, lambd))
        env.run(until=quantity)
        return self.numbers

    def generate_erl(self, quantity, low_bound, high_bound, lambd, order):
        env = simpy.Environment()
        env.process(self.write_random_numbers_erl(env, low_bound, high_bound, lambd, order))
        env.run(until=quantity)
        return self.numbers

    def write_random_numbers(self, env, low_bound, high_bound):
        self.numbers = []
        while True:
            value = int(random.random()*(high_bound - low_bound) + low_bound)
            self.numbers.append(value)
            yield env.timeout(1)

    def write_random_numbers_exp(self, env, low_bound, high_bound, lambd):
        self.numbers = []
        while True:
            value = random.expovariate(1/lambd)
            self.numbers.append(value)
            yield env.timeout(1)

    def write_random_numbers_erl(self, env, low_bound, high_bound, lambd, order):
        self.numbers = []
        while True:
            value = 0
            for i in range(order):
                value += random.expovariate(order/lambd)
            self.numbers.append(value)
            yield env.timeout(1)

def write_data(worksheet, init_column, statistics, chart, name):
    worksheet.write(0,init_column,"Interval")
    worksheet.write(0,init_column+1,"Quantity")
    
    for i in range(len(statistics[0])):
        worksheet.write(i+1,init_column,"%i - %i" % (statistics[0][i][0],statistics[0][i][1]))
        worksheet.write(i+1,init_column+1,statistics[1][i])

    chart.add_series({
        'values': [worksheet.name] + [1,init_column+1] + [len(statistics_reg[0]), init_column+1],
        'categories': [worksheet.name] + [1,init_column] + [len(statistics_reg[0]), init_column],
        'name': name,
    })

if __name__ == "__main__":
    quantity_of_columns = 20
    quantity_of_numbers = 20000
    low_bound = 0
    high_bound = 5000

    generator = Generator()
    statistics_reg = generator.generate_statistics(quantity_of_columns, quantity_of_numbers, low_bound, high_bound)
    statistics_exp = generator.generate_statistics_exp(quantity_of_columns, quantity_of_numbers, low_bound, high_bound, 1000)
    statistics_erl = generator.generate_statistics_erl(quantity_of_columns, quantity_of_numbers, low_bound, high_bound, 1000, 4)
    

    workbook = xlsxwriter.Workbook('new_test.xlsx')
    chart = workbook.add_chart({'type': 'column'})
    chart.set_y_axis({'name': 'Quantity'})
    chart.set_x_axis({'name': 'Interval'})
    chart.set_title({'name': 'Random numbers'})
    
    worksheet = workbook.add_worksheet()

    write_data(worksheet, 0, statistics_reg, chart, "Regular")
    write_data(worksheet, 3, statistics_exp, chart, "Exponential")
    write_data(worksheet, 6, statistics_erl, chart, "Erlang's")

    chart.set_size({'width': 720, 'height': 480})
    
##
    worksheet.insert_chart('J1', chart)
    workbook.close()
    
