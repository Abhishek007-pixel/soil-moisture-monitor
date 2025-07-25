# 🌱 Soil Moisture Monitoring System using PSoC and MATLAB

A real-time soil moisture monitoring system built with the **PSoC 5LP** microcontroller and a capacitive moisture sensor. The project displays moisture levels on an **LCD** and sends detailed readings over **USB UART** to a **MATLAB GUI**, where values are visualized live.

---

## 📦 Project Structure

soil-moisture-monitor/
├── psoc_project/
│ ├── main.c
│ ├── screenshots/
│ │ ├── cydwr_pin_config.png
│ │ ├── design_circuit.png
│ │ └── clock_config.png
├── matlab_script/
│ └── soil_moisture_plot.m
├── README.md



---

## 🔧 Hardware & Tools

- **Microcontroller**: CY8C5868AXI-LP035 (PSoC 5LP)
- **Sensor**: Capacitive Soil Moisture Sensor (Analog Output)
- **Display**: 16x2 Character LCD
- **Connectivity**: USB UART (USBUART)
- **Software**:
  - PSoC Creator
  - MATLAB

---

## 🔌 Pin Configuration (Design01.cydwr)

| Function         | Port/Pin   |
|------------------|------------|
| ADC Input        | P0[2]      |
| Sensor Input     | P0[4]      |
| LCD Port         | P2[6:0]    |
| UART (USB D+)    | P15[6]     |
| UART (USB D-)    | P15[7]     |

🖼 **Pin Configuration View**  
![Pin Configuration](./psoc_project/screenshots/cydwr_pin_config.png)

---

## 🧠 System Design

### 🔲 TopDesign.cysch Schematic

- **ADC_SAR**: Reads analog moisture sensor voltage.
- **Character LCD**: Displays real-time ADC and voltage values with moisture status (Wet, Moist, Dry).
- **UART (USBUART)**: Sends formatted string to PC.

🖼 **TopDesign Schematic**  
![Schematic](./psoc_project/screenshots/design_circuit.png)

---

## ⏱ Clock Configuration

- Master Clock: 24 MHz (PLL)
- USB Clock: 48 MHz (IMOx2)

🖼 **System Clock Setup**  
![Clock](./psoc_project/screenshots/clock_config.png)

---

## 📄 main.c (PSoC Firmware)

The main firmware performs:

- ADC conversion from sensor
- Voltage scaling
- Moisture state decision logic
- LCD display update
- UART transmission to MATLAB

📁 File: [`main.c`](./psoc_project/main.c)

---

## 💻 MATLAB GUI

The MATLAB script continuously reads USB serial data and updates a UI with moisture state and voltage values.

### 🔁 Features:
- Live text-based display
- Reads from COM port (adjustable)
- Handles incorrect formats gracefully

📁 File: [`soil_moisture_plot.m`](./matlab_script/soil_moisture_plot.m)

### 🔍 Sample Console Output:

Moisture: Moist, Voltage: 3.12 V
Moisture: Wet, Voltage: 1.48 V

y
---
## Results

### Setup and Monitoring
![Setup](./RS1.jpeg)

### Soil Moisture Output on LCD
![Sensor Close-up](./RS2.jpeg)


## 📊 Output Preview (Live Text UI)

| Moisture: Dry |
| Voltage: 4.12 V |


we can improve this by adding real-time plotting or data logging (see Future Work).

---

## 🚀 Future Improvements

- Add real-time voltage vs. time plot in MATLAB
- Log data to CSV for analysis
- Add buzzer alert for “Dry” state
- Extend to Bluetooth/LoRa for wireless transmission
- Package into a full IoT monitoring solution

---

## 📚 Learnings & Skills

- PSoC component configuration (ADC, UART, LCD)
- Serial communication (USBUART + MATLAB)
- Real-time UI handling in MATLAB
- Analog sensor interfacing and scaling
- Embedded system design from sensor to PC interface

---

## 📜 License

This project is released under the [MIT License](LICENSE).

---

## 🙌 Acknowledgements

Made as part of an academic mini project using Cypress PSoC Creator and MATLAB. Thanks to the documentation, forums, and lab tools that helped make this work!
