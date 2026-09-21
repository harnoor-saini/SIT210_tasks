const express = require("express");
const path = require("path");
require("dotenv").config();

const app = express();

app.use(express.json());

app.use(express.static(path.join(__dirname, "..", "frontend")));

app.post("/control", async (req, res) => {
    const { pin, value } = req.body;

    try {
        const response = await fetch(
            `https://blynk.cloud/external/api/update?token=${process.env.BLYNK_AUTH_TOKEN}&${pin}=${value}`
        );

        if (!response.ok) {
            throw new Error("Blynk request failed");
        }

        res.json({ success: true });
    }
    catch (error) {
        console.error(error);
        res.status(500).json({ success: false });
    }
});

app.listen(3000, () => {
    console.log("Server running at http://localhost:3000");
});