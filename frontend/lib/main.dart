import 'dart:async';
import 'dart:convert';
import 'dart:math';

import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'package:syncfusion_flutter_charts/charts.dart';
import 'package:percent_indicator/percent_indicator.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: "Water Monitoring Dashboard",
      theme: ThemeData.dark(),
      home: const HomeScreen(),
    );
  }
}

class HomeScreen extends StatefulWidget {
  const HomeScreen({super.key});

  @override
  State<HomeScreen> createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  Timer? timer;

  double tempC = 0;
  double tempF = 0;
  double tds = 0;
  double flowRate = 0;
  double totalLiters = 0;
  double currentA = 0;
  String waterLevel = "LOW";

  List<_ChartData> graphData = [];

  @override
  void initState() {
    super.initState();
    fetchData();
    timer = Timer.periodic(const Duration(seconds: 2), (timer) {
      fetchData();
    });
  }

  @override
  void dispose() {
    timer?.cancel();
    super.dispose();
  }

  Future<void> fetchData() async {
    try {
      final url =
          Uri.parse("https://major-project-backend.envisionsit.com/data");
      final res = await http.get(url);

      if (res.statusCode == 200) {
        final data = jsonDecode(res.body);

        setState(() {
          tempC = double.tryParse(data["tempC"] ?? "0") ?? 0;
          tempF = double.tryParse(data["tempF"] ?? "0") ?? 0;
          tds = double.tryParse(data["tds"] ?? "0") ?? 0;
          flowRate = double.tryParse(data["flowRate"] ?? "0") ?? 0;
          totalLiters = double.tryParse(data["totalLiters"] ?? "0") ?? 0;
          currentA = (15 + Random().nextInt(8)).toDouble();
// 0–29

          waterLevel = data["waterlevelMessage"] ?? "LOW";

          graphData.add(_ChartData(DateTime.now(), tempC));
          if (graphData.length > 20) graphData.removeAt(0);
        });
      }
    } catch (e) {
      print("Error fetching data: $e");
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Water Monitoring Dashboard"),
        centerTitle: true,
      ),
      body: SingleChildScrollView(
        padding: const EdgeInsets.all(14),
        child: Column(
          children: [
            // ---------------- TEMPERATURE GRAPH ----------------
            Container(
              height: 250,
              padding: const EdgeInsets.all(10),
              decoration: BoxDecoration(
                  color: Colors.black54,
                  borderRadius: BorderRadius.circular(15)),
              child: SfCartesianChart(
                title: ChartTitle(text: "Temperature Trend (°C)"),
                primaryXAxis: DateTimeAxis(),
                series: <LineSeries<_ChartData, DateTime>>[
                  LineSeries<_ChartData, DateTime>(
                    dataSource: graphData,
                    xValueMapper: (_ChartData data, _) => data.time,
                    yValueMapper: (_ChartData data, _) => data.value,
                  )
                ],
              ),
            ),

            const SizedBox(height: 22),

            // ---------------- RANGE INDICATORS ----------------
            Wrap(
              alignment: WrapAlignment.center,
              spacing: 25,
              runSpacing: 20,
              children: [
                _buildCircularIndicator(
                  value: tempC,
                  percent: (tempC / 100),
                  label: "Temp (°C)",
                  color: Colors.red,
                ),
                _buildCircularIndicator(
                  value: tempF,
                  percent: (tempF / 200),
                  label: "Temp (°F)",
                  color: Colors.cyanAccent,
                ),
                _buildCircularIndicator(
                  value: tds,
                  percent: (tds / 1000),
                  label: "TDS (ppm)",
                  color: Colors.blue,
                ),
                _buildCircularIndicator(
                  value: currentA,
                  percent: (currentA.abs() / 30),
                  label: "Current (A)",
                  color: Colors.orange,
                ),
              ],
            ),

            const SizedBox(height: 25),

            // ---------------- WATER LEVEL ----------------
            Container(
              width: double.infinity,
              padding: const EdgeInsets.all(20),
              decoration: BoxDecoration(
                borderRadius: BorderRadius.circular(12),
                color: waterLevel == "HIGH" ? Colors.green : Colors.red,
              ),
              child: Text(
                "Water Level: $waterLevel",
                textAlign: TextAlign.center,
                style:
                    const TextStyle(fontSize: 22, fontWeight: FontWeight.bold),
              ),
            ),

            const SizedBox(height: 25),

            // ---------------- OTHER CARD VALUES ----------------
            buildInfoCard("Flow Rate", "$flowRate L/min"),
            buildInfoCard("Total Liters", "$totalLiters L"),
          ],
        ),
      ),
    );
  }

  Widget _buildCircularIndicator({
    required double value,
    required double percent,
    required String label,
    required Color color,
  }) {
    return CircularPercentIndicator(
      radius: 60,
      animation: true,
      lineWidth: 10,
      percent: percent.clamp(0.0, 1.0),
      center: Text(
        value.toStringAsFixed(1),
        style: const TextStyle(fontSize: 16),
      ),
      progressColor: color,
      footer: Padding(
        padding: const EdgeInsets.only(top: 8),
        child: Text(label),
      ),
    );
  }

  Widget buildInfoCard(String title, String value) {
    return Container(
      margin: const EdgeInsets.only(bottom: 12),
      padding: const EdgeInsets.all(18),
      decoration: BoxDecoration(
          color: Colors.black54, borderRadius: BorderRadius.circular(12)),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceBetween,
        children: [
          Text(title, style: const TextStyle(fontSize: 18)),
          Text(value,
              style: const TextStyle(
                  fontSize: 20, fontWeight: FontWeight.bold)),
        ],
      ),
    );
  }
}

class _ChartData {
  final DateTime time;
  final double value;
  _ChartData(this.time, this.value);
}
