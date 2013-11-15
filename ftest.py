event_positions = [];
for x in range(0,25):
    event_positions.append(0) 

def intializelist(event_positions):
    for count in range(1,len(event_positions)):
        if count < 11:
            event_positions[count] = 1
        elif count < 19:
            event_positions[count] = 2
        elif count <  24:
            event_positions[count] = 3
intializelist(event_positions)
