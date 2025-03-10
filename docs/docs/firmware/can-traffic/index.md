# Calculating CAN Traffic

In order to calculate the CAN load, we must define a few variables related to the CAN protocol.

## Baud

The baud rate is the rate at which data is transfered in a communication channel (like CAN). For example, 9600 Baud rate is 9600 bits per second

## Frequency

The frequency of a message, expressed in (Hz), is how often a message is transmitted per second. Different messages can have different frequencies.

This variation affects the total bits transmitted and, in turn, the bus load. To calculate bits per second, consider each message’s frequency and whether their lengths differ.

## Message Length

The message length in a CAN frame can be calculated as a function of the data length. This calculation includes several fixed fields and a variable data field, which changes based on the message's data content.

<figure markdown="span">
![Can Frame Bits](img/can-frame-Light.png#only-light)
![Can Frame Bits](img/can-frame-Dark.png#only-dark)
<figcaption>Standard CAN frame bit composition.<br>Adapted from <a href="https://www.csselectronics.com/pages/can-bus-simple-intro-tutorial">CSS Electronics</a></figcaption>
</figure>

Each CAN frame consists of several fields with fixed bit lengths, plus a variable-length data field. The total frame length is:

\[ 1 + 11 + 1 + 6 + 8x + 16 + 2 + 7 = 44 + 8x \text{ bits}\]

where \(x\) represents the number of bytes in the data field.

--------------------------------------

## Total CAN Traffic

We must multiply total bits per second by 1.2 to account for bit stuffing

\begin{align}
\text{Total Bits Per Second} &= 1.2 \times \sum_{i=1}^n \left(\text{Frequency}_i \times \text{Message Length}_i \right)
\end{align}

## Total Bus Load

\begin{align}
\text{Bus Load}\% = \frac{\text{Total Bits per Second}}{\text{Baud Rate}} \times 100\%
\end{align}

--------------------------------------

## Sample calculation

**Given**:

Baud Rate: 500 kbaud (500,000 bits transferred per second)

|Message Type | Data Length| Frequency (Hz)| Message Length (Bits)|
|--------------|------------|---------------|---------------------|
|Battery Status|     8      |     100       | \(44 + 8 \times 8 = 108\)|
|Motor Control|      5      |     50        | \(44 + 8 \times 5 = 84\)|

\begin{align}
\text{Total Bits Per Second} &= 1.2 \times \sum_{i=1}^n \left(\text{Frequency}_i \times \text{Message Length}_i \right)\\
\text{Total Bits Per Second} &= 1.2 \times \left((100\text{ Hz} \times 108\text{ bits}) + (50\text{ Hz} \times 84\text{ bits})\right)\\
&= 1.2 \times \left(10800 + 4200\right)\text{ bits per second}\\
&= 1.2 \times 15000\text{ bits per second}\\
&= 18000\text{ bits per second}
\end{align}

The bus load is the previous example can be calculated as:

$$
\text{Bus Load}\% = \frac{\text{Total Bits per Second}}{\text{Baud Rate}} \times 100\%
$$

$$
\text{Bus Load} = \left(\frac{18000}{500000}\right) \times 100\% = 3.60\%
$$
