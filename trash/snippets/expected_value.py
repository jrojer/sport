from random import randint


def successful_event(p):
    val = 10**6
    return randint(0,val) < p*val


def expected_value(p):
    n = 10**5
    total_num_trials = 0
    for i in range(n):
        num_trials_until_first_success = 1
        while(not successful_event(p)):
            num_trials_until_first_success += 1
        total_num_trials += num_trials_until_first_success
    return total_num_trials/n

print(expected_value(0.01))
