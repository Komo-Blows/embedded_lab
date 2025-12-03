# Number of clock cycles for min, half and max positions for the servo motors
| Angle (Degrees)  | Duty Cycle (ms)   |   Duty Cycle (50MHz Ticks)|
|---|---|---|
|-90|.05   | 25000   |
| 0  | 1.5  |  75000 |
|  90 | 2.5  |  125000 |
# Develop Alg to translate an input amgle between -90 and 90 to respective clock cycle
$$\text{clock cycles} = 25000 + 1250(\text{angle} + 90) $$

# Write equation that translates a speed to a delay value, where 100 speed is equal to a deay of 1000 cycles, and 0 speed is equal to a delay of 1700 cycles
$$(\text{speed}*7)+1000 = \text{cycles}$$
