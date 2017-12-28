import simpy

def car(env):
    while True:
        print("Start parking at %d" % env.now)
        parking_duration = 500
        yield env.timeout(parking_duration)

        print("Start driving at %d" % env.now)
        driving_duration = 2
        yield env.timeout(driving_duration)

if __name__ == "__main__":
    env = simpy.Environment()
    env.process(car(env))
    env.run(until=3000)
