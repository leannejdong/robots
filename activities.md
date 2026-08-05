# Teaching Note: Edison Robot - Barcodes vs. EdScratch (Obstacle Avoidance)

**Class Prompt / Hook:**  
*Class, do you remember our barcodes from Week 1? Today, we are going to learn about the actual program behind those barcodes, starting with obstacle avoidance!*

---

## Overview

When we scanned the "Obstacle Avoidance" barcode in Week 1, Edison executed a pre-programmed script stored directly inside its internal firmware. In EdScratch, we write the step-by-step logic ourselves to achieve the same movement.

---

## Comparison Summary

| Feature | Barcode Scanning ("Obstacle Avoidance") | Custom Coding in EdScratch |
| :--- | :--- | :--- |
| **How It Works** | Reads a fixed sequence stored in Edison's firmware. | Downloads your step-by-step block code via the USB cable. |
| **Sensor Setup** | Automatically enables infrared (IR) emitters and receivers. | Requires turning on IR detection explicitly using setup blocks. |
| **Control & Customization** | None. Edison moves, detects, turns, and continues on a pre-set loop. | High. You decide how far to turn, how fast to drive, or whether to sound an alarm. |
| **Logic Structure** | Hidden "black box" algorithm. | Explicit loop structure using `forever`, `if...then` blocks, and `obstacle detected` events. |

---

## Key Discussion Points for Students

1. **Barcode (Pre-made Shortcut):**  
   The barcode tells Edison to run a hidden, built-in program. Edison does the thinking for us.

2. **EdScratch (Programmer Control):**  
   In EdScratch, **you** are the programmer. You control the exact sensing, decision-making, and physical reaction when Edison encounters an obstacle.

---

## Teaching Sequence / Activity Steps

1. **Review Week 1:** Ask students to recall how Edison reacted when scanning the "Obstacle Avoidance" barcode.
2. **Deconstruct the Behavior:** Ask students to list the exact physical steps Edison takes when it encounters an obstacle (e.g., *Drive forward → Detect obstacle → Stop → Backup/Turn → Resume driving*).
3. **Replicate in EdScratch:** Guide students to build the program block-by-block in EdScratch using the IR detection setup, `forever` loop, and conditional blocks.
   
