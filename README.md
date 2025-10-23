# Blinky for NUCLEO-C071RB

Simple LED blink example for STM32C071RB that compiles on GitHub - no local tools needed!

## 🎯 What This Does
Blinks the green LED (LD4) on your NUCLEO-C071RB board every ~500ms.

## 📁 Files
- `main.c` - Blinky code
- `startup.c` - Minimal startup code  
- `STM32C071RBTx.ld` - Linker script (32KB Flash, 12KB RAM)
- `.github/workflows/build.yml` - GitHub Actions build

## 🚀 Quick Setup (5 minutes!)

### Step 1: Create GitHub Repository
1. Go to https://github.com/new
2. Name: `nucleo-c071rb-blinky`
3. Select "Add a README file"
4. Click "Create repository"

### Step 2: Upload These Files
1. In your new repo, click "Add file" → "Upload files"
2. Drag all 4 files here
3. Make sure to create the folder structure:
   ```
   main.c
   startup.c
   STM32C071RBTx.ld
   .github/workflows/build.yml
   ```
4. Click "Commit changes"

### Step 3: Get Your Firmware!
1. Go to "Actions" tab
2. Click on the build (it starts automatically!)
3. When done (green ✓), click the build
4. Download "firmware" artifact
5. Extract to get `firmware.bin`

## 💾 Flash to Your Board

### Using STM32CubeProgrammer:
1. Connect NUCLEO board via USB
2. Open STM32CubeProgrammer
3. Click Connect
4. Open `firmware.bin`
5. Click Download

### Using command line (st-flash):
```bash
st-flash write firmware.bin 0x8000000
```

### Using drag-and-drop (if supported):
1. Connect NUCLEO board
2. It appears as USB drive
3. Copy `firmware.bin` to the drive

## ✅ Success!
The green LED (LD4) should now be blinking!

## 📝 Making Changes
1. Edit `main.c` on GitHub (click pencil icon)
2. Change `delay(400000)` to make it faster/slower
3. Commit changes
4. GitHub rebuilds automatically
5. Download new firmware from Actions

## 🔧 Customization
- LED is on PA5 (pin 5 of GPIOA)
- Clock is default 12MHz HSI
- No HAL, pure register access for simplicity

## 📊 Memory Usage
- Flash: ~500 bytes (of 32KB)
- RAM: ~1KB stack (of 12KB)

Perfect for learning embedded programming!
