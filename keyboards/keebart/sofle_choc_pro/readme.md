# Sofle Choc Pro

![sofle_choc_pro](https://i.imgur.com/q9A2HMe.jpeg)

A complete remake of the Sofle Choc Keyboard by Josef Adamčík. Featuring an onboard RP2040 with 128 MB flash
memory and choc-spaced keys for a more compact keyboard.

- Keyboard Maintainer: [Keebart](https://github.com/Keebart)
- Hardware Supported: RP2040
- Hardware Availability: [Keebart Shop](https://keebart.com/products/sofle)

Make example for this keyboard (after setting up your build environment):

    make keebart/sofle_choc_pro:default

Flashing example for this keyboard:

    make keebart/sofle_choc_pro:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

- **Bootmagic reset**: Hold down the top left key of the left side of the keyboard while connecting the left side to the computer. Similarly, hold down the top right key of the right side of the keyboard while connecting the right side to the computer.
- **Physical reset button**: Briefly press the button on the back of the PCB
- **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

# Key indexes

## **Left Half** (rows 0–4, cols 0–5, thumbs: [4,0]–[4,4])

```
[ 26][ 25][ 24][ 23][ 22][ 21]
[ 13][ 12][ 11][ 10][  9][  8]
[  0][  1][  2][  3][  4][  5]
[ 14][ 15][ 16][ 17][ 18][ 19]
    [ 48][ 49][ 50][ 51][ 52]
```

## **Right Half** (rows 5–9, cols 0–5, thumbs: [9,0]–[9,4])

```
[ 56][ 55][ 54][ 53][ 52][ 51]
[ 43][ 42][ 41][ 40][ 39][ 38]
[ 30][ 31][ 32][ 33][ 34][ 35]
[ 44][ 45][ 46][ 47][ 48][ 49]
    [ 57][ 58][ 59][ 60][ 61]
```

**Note:**

- The numbers in brackets are the RGB matrix indices.
- The arrangement is based on the order in your `"rgb_matrix"` → `"layout"` array and the physical layout described by `"LAYOUT_split_4x6_5"`.

---

### **How to Use**

- To set the color for a key, use the index shown in the diagram with `rgb_matrix_set_color(index, ...)`.
- For example, the top left key on the left split (`[0,0]`) is index **26**.
- The top right key on the right split (`[5,5]`) is index **56**.
