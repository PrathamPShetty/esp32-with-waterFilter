const express = require("express");
const cors = require("cors");

const app = express();
app.use(cors());

// Use let so we can update the values
let tempC = 0;
let tempF = 0;
let tds = 0;
let flowRate = 0;
let totalLiters = 0;
let waterlevelMessage = "";
let currentA = 0;

app.get("/temp", (req, res) => {
  tempC = req.query.tempC;
  tempF = req.query.tempF;
  tds = req.query.tds;
  flowRate = req.query.flowRate;
  totalLiters = req.query.totalLiters;
  waterlevelMessage = req.query.waterlevel;
  currentA = req.query.currentA;

  console.log("📥 Temperature Received:");
  console.log("Temp C:", tempC);
  console.log("Temp F:", tempF);
  console.log("TDS Value:", tds);
  console.log("Flow Rate:", flowRate);
  console.log("Total Liters:", totalLiters);
  console.log("Water Level Message:", waterlevelMessage);
  console.log("Current A:", currentA);

  res.json({
    status: "success",
    message: "Temperature received",
  });
});

app.get("/data", (req, res) => {
  res.json({
    status: "success",
    tempC: tempC,
    tempF: tempF,
    tds: tds,
    flowRate: flowRate,
    totalLiters: totalLiters,
    waterlevelMessage: waterlevelMessage,
    currentA: currentA,
  });
});

// Server start
const PORT = 3000;
const IP = "0.0.0.0";
app.listen(PORT, IP, () => {
  console.log(`🚀 Server running on http://${IP}:${PORT}`);
});
