-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street";
.schema
SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 7;
SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 7 AND license_plate = "5P2BI95";
SELECT * FROM people WHERE license_plate = "5P2BI95";

SELECT * FROM interviews WHERE day = 28 AND month = 7;
SELECT * FROM bakery_security_logs WHERE day = 28 AND month = 7;
SELECT * FROM people WHERE license_plate = "1106N58";
SELECT * FROM people WHERE license_plate = "0NTHK55";
SELECT * FROM people WHERE license_plate = "322W7JE";
SELECT * FROM people WHERE license_plate = "L93JTIZ";
SELECT * FROM phone_calls WHERE year = 2021 AND day = 28 AND month = 7 AND duration < 60;
SELECT * FROM flights WHERE year = 2021 AND day = 29 AND month = 7;
SELECT * FROM airports WHERE id = 6;
