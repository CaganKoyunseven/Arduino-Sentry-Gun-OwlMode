# Arduino Sentry Gun (Owl Mode 🦉)

This project is an autonomous **Sentry Gun (Turret)** system powered by an Arduino Uno. It detects and tracks targets using dual ultrasonic sensors.

Unlike standard 360° turrets that tangle wires, this system implements a smart **"Owl Mode"** algorithm. It uses a continuous rotation servo but restricts movement to a safe arc (approx. 180°) using a virtual positioning system to protect internal wiring.

## 🚀 Key Features
* **Safety-Limited Rotation:** Although a 360° continuous servo is used, the code logically restricts movement to a safe range to prevent cable twisting (Cable Protection).
* **Dual Sensor Tracking:** Uses two HC-SR04 sensors (Left & Right) to determine target direction effectively.
* **Drift Compensation:** Includes specific code adjustments to handle mechanical motor asymmetry (Left/Right speed balancing).
* **Snappy Movement:** Optimized for short, fast, and precise movements rather than slow panning.

## 🛠️ Hardware & Pin Configuration

| Component | Arduino Pin | Notes |
| :--- | :--- | :--- |
| **Left Sensor (Trig)** | 8 | |
| **Left Sensor (Echo)** | 9 | |
| **Right Sensor (Trig)** | 10 | |
| **Right Sensor (Echo)** | 11 | |
| **Servo Motor** | 3 | Continuous Rotation (360) Servo |
| **Laser Module** | 13 | Active HIGH |
| **Buzzer** | 6 | Passive Buzzer |

## ⚙️ How It Works (The Logic)
1.  **Calibration:** On startup, the system calibrates based on the nearest object to define an "Attack Bound".
2.  **Scanning:** The turret scans left and right within the safety limits (`SafetyLimit` variable).
3.  **Tracking:** If an object breaks the Attack Bound, the turret turns towards the object using asymmetric speed settings to ensure straight tracking.
4.  **Firing:** When the target is centered (seen by both sensors), the laser activates, and the buzzer sounds.

## 🔧 Installation & Setup
1.  Download the `Sentry_Owl_Mode.ino` file.
2.  Open it in **Arduino IDE**.
3.  **Critical Adjustment:** Check the `StopPoint` variable.
    * Continuous servos vary. If your motor drifts when it should be stopped, change `90` to `89` or `91`.
4.  **Centering:** Before powering on, manually center the turret head. The code assumes the startup position is the center (0).
5.  Upload the code and enjoy!

## ⚠️ Note on Rotation
Please note that while this project uses a 360-degree motor, **it does not rotate continuously in a full circle.** This is intentional design behavior to allow the use of wired components (Laser, Sensors) without a slip ring.

---
*Developed by [Cagan Koyunseven /CaganKoyunseven]*
