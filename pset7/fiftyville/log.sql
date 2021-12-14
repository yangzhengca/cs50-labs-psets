Start Clues:
-- 0 - 2020.7.28, Chamberlin Street

SELECT description FROM crime_scene_reports WHERE street = "Chamberlin Street" and year = 2020 and month = 7 and day = 28;
-- description: Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted 
-- today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

Find Clues:
-- 0.0 - 10:15am
-- 0.1 - three witnesses and each mentions the courthouse -> interview


-- Folloe Clue of three witness
SELECT name, transcript FROM interviews WHERE year = 2020 and month = 7 and day = 28 and transcript LIKE "%courthouse%";
-- name | transcript
-- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

Find Clues:
-- 0.1.0 - leave between 10:15am - 10:25am -> courthouse_security_logs
-- 0.1.1 - Before 10:15am, the ATM on Fifer Street, withdrawing -> atm_transactions, bank_accounts
-- 0.1.2 - As leaving the courthouse, less than a minute -> phone_calls
-- 0.1.3 - earliest flight tomorrow, purchase after the phone call -> flights


-- Follow Clue 0.1.0 - courthouse_security_logs
SELECT activity,license_plate FROM courthouse_security_logs WHERE year = 2020 and month = 7 and day = 28 and hour = 10 and minute > 15 and minute <25;
-- activity | license_plate
-- exit | 5P2BI95
-- exit | 94KL13X
-- exit | 6P58WS2
-- exit | 4328GD8
-- exit | G412CB7
-- exit | L93JTIZ
-- exit | 322W7JE
-- exit | 0NTHK55

SELECT name FROM people WHERE license_plate in (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 and month = 7 and day = 28 and hour = 10 and minute > 15 and minute <25);
-- name
-- Patrick
-- Amber
-- Elizabeth
-- Roger
-- Danielle
-- Russell
-- Evelyn
-- Ernest

Find Clues:
-- 0.1.0.0 - The thief is in (Patrick, Amber, Elizabeth, Roger, Danielle, Russell, Evelyn, Ernest)


-- Follow Clue 0.1.1 - atm_transactions, bank_accounts
SELECT account_number FROM atm_transactions WHERE year = 2020 and month = 7 and day = 28 and transaction_type = "withdraw" and atm_location = "Fifer Street";
-- account_number
-- 28500762
-- 28296815
-- 76054385
-- 49610011
-- 16153065
-- 25506511
-- 81061156
-- 26013199

SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 and month = 7 and day = 28 and transaction_type = "withdraw" and atm_location = "Fifer Street");
-- name
-- Ernest
-- Russell
-- Roy
-- Bobby
-- Elizabeth
-- Danielle
-- Madison
-- Victoria

Find Clues:
-- 0.1.1.0 - The thief is in (Ernest, Russell, Roy, Bobby, Elizabeth, Danielle, Madison, Victoria)


-- Follow clue 0.1.0.0 and 0.1.1.0
SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 and month = 7 and day = 28 and transaction_type = "withdraw" and atm_location = "Fifer Street") and name IN (SELECT name FROM people WHERE license_plate in (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 and month = 7 and day = 28 and hour = 10 and minute > 15 and minute <25));
-- name
-- Ernest
-- Russell
-- Elizabeth
-- Danielle

Find Clues:
-- 0.1.1.0.0 - The thief is in (Ernest, Russell, Elizabeth, Danielle)

-- Follow Clue 0.1.2
SELECT caller FROM phone_calls WHERE year = 2020 and month = 7 and day = 28 and duration < 60;
-- caller
-- (130) 555-0289
-- (499) 555-9472
-- (367) 555-5533
-- (499) 555-9472
-- (286) 555-6063
-- (770) 555-1861
-- (031) 555-6622
-- (826) 555-1652
-- (338) 555-6650

SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 and month = 7 and day = 28 and duration < 60);
-- name
-- Bobby
-- Roger
-- Victoria
-- Madison
-- Russell
-- Evelyn
-- Ernest
-- Kimberly

Find Clue:
-- 0.1.2.0 The thief is in (Bobby, Roger, Victoria, Madison, Russell, Evelyn, Ernest, Kimberly)

-- Follow clue 0.1.1.0.0 and 0.1.2.0
SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 and month = 7 and day = 28 and transaction_type = "withdraw" and atm_location = "Fifer Street") and name IN (SELECT name FROM people WHERE license_plate in (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 and month = 7 and day = 28 and hour = 10 and minute > 15 and minute <25)) and name IN (SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 and month = 7 and day = 28 and duration < 60));
-- name
-- Ernest
-- Russell

Find Clue:
-- 0.1.2.0.0 The thief is in (Ernest, Russell)


-- Follow clue 0.1.3 and 0.1.2.0.0
SELECT name FROM people WHERE name IN ("Ernest", " Russell") and passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville") and year = 2020 and month = 7 and day = 29 ORDER BY hour LIMIT 1));
-- name
-- Ernest


Find Answer:
-- 1 - The thief is Ernest.


-- Follow answer 1
SELECT city FROM airports JOIN flights ON airports.id = flights.destination_airport_id JOIN passengers ON flights.id = passengers.flight_id JOIN people ON passengers.passport_number = people.passport_number WHERE name = "Ernest";
-- city
-- London

Find Answer:
-- 2 - Escape to London.


-- Follow answer 1 and clue 0.1.2
SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.receiver WHERE caller = (SELECT phone_number FROM people WHERE name = "Ernest") and year = 2020 and month = 7 and day = 28 and duration < 60;
-- name
-- Berthold

Find Answer:
-- 3 - The ACCOMPLICE is Berthold.