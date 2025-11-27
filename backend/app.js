const express = require("express");
const cors = require("cors");

const app = express();
app.use(cors());


app.get("/temp", (req, res) => {
  const tempC = req.query.tempC;
  const tempF = req.query.tempF;

  console.log("📥 Temperature Received:");
  console.log("Temp C:", tempC);
  console.log("Temp F:", tempF);

  res.json({
    status: "success",
    message: "Temperature received",
  });
});

// Server start
const PORT = 3000;
const IP = "0.0.0.0";
app.listen(PORT, IP, () => {
  console.log(`🚀 Server running on http://${IP}:${PORT}`);
});
