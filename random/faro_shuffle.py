import math

def main():
    answer = faro_cycles(6)
    print(answer)
    return

def faro_cycles(deck_size):
    if deck_size % 2 != 0:
        return -1

    deck = [*range(deck_size)]

    count = 0
    sentinel = deck[1]
    done = False
    while True:
        deck = faro_shuffle(deck)
        count += 1
        if deck[1] == sentinel:
            break
    return count

def faro_shuffle(deck):
    print('deck: ')
    print(deck)
    result = [deck[0]]
    mid = math.floor(len(deck)/2)
    print('mid ' + str(mid))

    lower = deck[0]
    lower_end = deck[mid]
    upper = deck[mid]
    upper_end = deck[len(deck)-1]+1

    print('lower size ' + str(lower_end - lower))
    print('upper size ' + str(upper_end - upper))
    
    while lower != lower_end and upper != upper_end:
        result.append(upper)
        lower += 1
        result.append(lower)
        upper += 1
    
    result = result[:-1]
    #deck.clear()
    #deck.extend(result[:])
    print('after')
    print(result)
    return result

main()

