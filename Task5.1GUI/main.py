import tkinter as tk
import RPi.GPIO as GPIO

# LED GPIO pins
LIVING_ROOM = 17
BATHROOM = 27
CLOSET = 22

GPIO.setmode(GPIO.BCM)

GPIO.setup(LIVING_ROOM, GPIO.OUT)
GPIO.setup(BATHROOM, GPIO.OUT)
GPIO.setup(CLOSET, GPIO.OUT)

def turn_on(pin):
    GPIO.output(LIVING_ROOM, GPIO.LOW)
    GPIO.output(BATHROOM, GPIO.LOW)
    GPIO.output(CLOSET, GPIO.LOW)

    GPIO.output(pin, GPIO.HIGH)

def exit_program():
    GPIO.cleanup()
    window.destroy()

window = tk.Tk()
window.title("HOUSE LIGHTS")
window.geometry("500x400")

title = tk.Label(window, text="HOUSE LIGHTS", font=("Times New Roman", 24))
title.pack(pady=30)

room = tk.IntVar()

living = tk.Radiobutton(
    window,
    text="Living Room",
    variable=room,
    value=1,
    command=lambda: turn_on(LIVING_ROOM),
    font=("Times New Roman", 20)
)
living.pack(pady=10)

bathroom = tk.Radiobutton(
    window,
    text="Bathroom",
    variable=room,
    value=2,
    command=lambda: turn_on(BATHROOM),
    font=("Times New Roman", 20)
)
bathroom.pack(pady=10)

closet = tk.Radiobutton(
    window,
    text="Closet",
    variable=room,
    value=3,
    command=lambda: turn_on(CLOSET),
    font=("Times New Roman", 20)
)
closet.pack(pady=10)

exit_button = tk.Button(
    window,
    text="Exit",
    command=exit_program,
    font=("Times New Roman", 19)
)
exit_button.pack(pady=25)

window.mainloop()