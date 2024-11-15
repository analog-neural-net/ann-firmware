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
![](img/canbusdiagram.svg){ width="100%" }
<figcaption>CAN Bus Frame Diagram. Source: <a href="https://www.csselectronics.com/pages/can-bus-simple-intro-tutorial">CSS Electronics CAN Bus Tutorial</a></figcaption>
</figure>

Each CAN frame consists of several fields with fixed bit lengths, plus a variable-length data field. Let \(x\) be the number of bytes. Here’s the breakdown:

|Frame Element| Length (bits)|
|--------------|------------|
|Start of Frame (SOF) |     1   |
|Identifier (ID)|      11     |
|Remote Transmission Request (RTR)| 1|
| Control (DLC)| 6|
|Data| 8 bits per byte with 20% bit stuffing = 9.6x|
|Cyclic Redundancy Check (CRC) | 16 |
|Acknowledgement (ACK)| 2 |
|End of Frame (EOF)| 7|

### Final Formula

The maximum total frame length is:

\[ 1 + 11 + 1 + 6 + 16 + 2 + 7 + 9.6x = 44 + 9.6x \text{ bits}\]

where \(x\) represents the number of bytes in the variable data field.

--------------------------------------

## Total CAN Traffic

\begin{align}
\text{Total Bits Per Second} &= \sum_{i=1}^n \left(\text{Frequency}_i \times \text{Message Length}_i \right)\\
\end{align}

## Total Bus Load

\begin{align}
\text{Bus Load}\%= \frac{\text{Total Bits per Second}}{\text{Baud Rate}} \times 100\%
\end{align}

--------------------------------------

## Sample calculation

**Given**:

Baud Rate: 500 kbaud (500,000 bits transferred per second)

|Message Type | Data Length| Frequency (Hz)| Message Length (Bits)|
|--------------|------------|---------------|---------------------|
|Battery Status|     8      |     100       | 44 + 9.6 x 8 = 121|
|Motor Control|      5      |     50        | 44 + 9.6 x 5 = 92|

\begin{align}
\text{Total Bits Per Second} &= \sum_{i=1}^n \left(\text{Frequency}_i \times \text{Message Length}_i \right)\\
\text{Total Bits Per Second} &= (100\text{ Hz} \times 121\text{ bits}) + (50\text{ Hz}\times 92\text{ bits})\\
&=(12100 + 4600)\text{ bits per second}\\
&= 16700\text{ bits per second}
\end{align}

The bus load is the previous example can be calculated as:

$$
\text{Bus Load}\%= \frac{\text{Total Bits per Second}}{\text{Baud Rate}} \times 100\%
$$

$$
\text{Bus Load} = \left(\frac{16700}{500,000}\right) \times 100\% = 3.34\%
$$
