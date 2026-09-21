async function controlLight(room, state) {

    let pin;

    if (room === "living room") {
        pin = "V0";
    }
    else if (room === "bathroom") {
        pin = "V1";
    }
    else if (room === "closet") {
        pin = "V2";
    }

    try {
        const response = await fetch("/control", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({
                pin: pin,
                value: state ? 1 : 0
            })
        });

        if (response.ok) {
            document.getElementById("status").innerText =
                room + " light is " + (state ? "ON" : "OFF");
        }
    }
    catch (error) {
        document.getElementById("status").innerText =
            "Connection error";
        console.error(error);
    }
}
