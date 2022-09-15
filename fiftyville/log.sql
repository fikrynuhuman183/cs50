-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT id,description FROM crime_scene_reports WHERE (month =7) AND (year=2021) AND (day=28) AND (street ="Humphrey Street");
SELECT license_plate,minute FROM bakery_security_logs WHERE year=2021 AND day=28 AND month=7 AND hour=10 AND activity="exit";
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year=2021 AND day=28 AND month=7 AND hour=10 AND minute>15);
--Suspects

SELECT name, transcript, day FROM interviews WHERE year=2021 AND month = 7;
--Withdraws money early morning
--catches the earliest flight out on July 29th
--accomplice buys ticket

--check for phone calls with duration lessthan a minute on day of theft and cross check them with the list of suspects
SELECT caller,receiver FROM phone_calls WHERE month=7 AND day=28 AND duration<60;
SELECT name FROM people WHERE name IN
   ...> FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year=2021 AND day=28 AND month=7 AND hour=10 AND minute>15))
   ...> AND phone_number IN (SELECT caller FROM phone_calls WHERE month=7 AND day=28 AND duration<60);

--suspects = Sofia, Taylor, Diana, Kelsey, Bruce
--check who has done transactions in the bank that day
SELECT people.name FROM people JOIN bank_accounts ON people.id=bank_accounts.person_id WHERE people.name IN ("Sofia","Taylor","Diana","Kelsey","Bruce")
AND bank_accounts.account_number IN (SELECT account_number FROM atm_transactions WHERE year=2021 AND month=7 AND day=28);

--people who did traansactoins are Bruce, diana and Taylor
--+--------+----------------+
--|  name  | account_number |
--+--------+----------------+
--| Bruce  | 49610011       |
--| Diana  | 26013199       |
--| Taylor | 76054385       |
--+--------+----------------+
--those who withdraw money
SELECT account_number FROM atm_transactions WHERE account_number IN (49610011, 26013199, 76054385)
AND year=2021 AND month=7 AND day=28 AND transaction_type="withdraw"; -- all three

--passport number
--+--------+-----------------+
--|  name  | passport_number |
--+--------+-----------------+
--| Taylor | 1988161715      |
--| Diana  | 3592750733      |
--| Bruce  | 5773159633      |
--+--------+-----------------+
--I am realizing I have made a mistake in including Taylor in the suspects list, c his exit has been delayed. So the only suspects are Diana and Bruce
SELECT * FROM airports;

--fiftyvile airport id = 8

SELECT id,hour,minute FROM flights WHERE origin_airport_id=8 AND year=2021 AND day=29 AND month = 7;
--earliest flight id is 36 which is at 8.20 am

SELECT passport_number FROM passengers WHERE flight_id=36 AND passport_number IN (3592750733,5773159633);
--Only bruce have traveled in this flight
--Bruce is the thief
--phone numbers of bruce
--+--------+----------------+
--|  name  |  phone_number  |
--+--------+----------------+
--| Bruce  | (367) 555-5533 |
--+--------+----------------+

--find out the person called by bruce
SELECT caller,receiver FROM phone_calls WHERE month=7 AND day=28 AND duration<60 AND caller IN ("(286) 555-6063","(367) 555-5533");
--+----------------+----------------+
--|     caller     |    receiver    |
--+----------------+----------------+
--| Bruce  (367) 555-5533 | Robin (375) 555-8161 |
--+----------------+----------------+
--Obtain the name of the accomplice using reciever phone number

--| Robin | (375) 555-8161 |                 |
--+-------+----------------+-----------------+

-
 --The traveled to New York City with id 4
--imterviws
--| I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
--| As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
