import tkinter as tk
import RPi.GPIO as GPIO

# GPIO pins
LIVING_ROOM = 18
BATHROOM = 27
CLOSET = 22

GPIO.setmode(GPIO.BCM)

GPIO.setup(LIVING_ROOM, GPIO.OUT)
GPIO.setup(BATHROOM, GPIO.OUT)
GPIO.setup(CLOSET, GPIO.OUT)

# PWM for living room
pwm = GPIO.PWM(LIVING_ROOM, 1000)
pwm.start(0)


def living_room():
    pwm.ChangeDutyCycle(intensity.get())
    GPIO.output(BATHROOM, GPIO.LOW)
    GPIO.output(CLOSET, GPIO.LOW)


def bathroom():
    pwm.ChangeDutyCycle(0)
    GPIO.output(BATHROOM, GPIO.HIGH)
    GPIO.output(CLOSET, GPIO.LOW)


def closet():
    pwm.ChangeDutyCycle(0)
    GPIO.output(BATHROOM, GPIO.LOW)
    GPIO.output(CLOSET, GPIO.HIGH)


def change_intensity(value):
    if living_button["relief"] == "sunken":
        pwm.ChangeDutyCycle(float(value))


def exit_program():
    pwm.stop()
    GPIO.cleanup()
    window.destroy()


window = tk.Tk()
window.title("Smart Home")
window.geometry("500x500")
window.configure(bg="black")


title = tk.Label(
    window,
    text="SMART HOME",
    font=("Arial", 26, "bold"),
    bg="black",
    fg="white"
)
title.pack(pady=35)


# Room buttons
living_button = tk.Button(
    window,
    text="Living Room",
    command=living_room,
    width=15,
    height=2,
    font=("Arial", 14),
    bg="#222222",
    fg="white",
    activebackground="#444444",
    activeforeground="white",
    relief="raised",
    bd=2
)
living_button.pack(pady=8)


bathroom_button = tk.Button(
    window,
    text="Bathroom",
    command=bathroom,
    width=15,
    height=2,
    font=("Arial", 14),
    bg="#2478d4",
    fg="white",
    activebackground="#185a9d",
    activeforeground="white",
    relief="raised",
    bd=2
)
bathroom_button.pack(pady=8)


closet_button = tk.Button(
    window,
    text="Closet",
    command=closet,
    width=15,
    height=2,
    font=("Arial", 14),
    bg="#2478d4",
    fg="white",
    activebackground="#185a9d",
    activeforeground="white",
    relief="raised",
    bd=2
)
closet_button.pack(pady=8)


# Intensity slider
intensity = tk.Scale(
    window,
    from_=0,
    to=100,
    orient=tk.HORIZONTAL,
    length=300,
    label="Living Room Intensity",
    font=("Arial", 11),
    bg="black",
    fg="white",
    troughcolor="#333333",
    highlightthickness=0,
    activebackground="#2478d4"
)
intensity.set(50)
intensity.pack(pady=20)


# Exit
exit_button = tk.Button(
    window,
    text="Exit",
    command=exit_program,
    width=12,
    height=2,
    font=("Arial", 13),
    bg="#333333",
    fg="white",
    activebackground="#555555",
    activeforeground="white",
    relief="raised",
    bd=2
)
exit_button.pack(pady=10)


window.mainloop()
