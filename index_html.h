<!DOCTYPE html>
<html>
<head>
  <title>Firebase Relay Dashboard</title>
  <script src="https://www.gstatic.com/firebasejs/9.22.0/firebase-app-compat.js"></script>
  <script src="https://www.gstatic.com/firebasejs/9.22.0/firebase-database-compat.js"></script>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      padding: 50px;
    }
    button {
      padding: 15px 30px;
      font-size: 20px;
      margin: 10px;
      border-radius: 8px;
      border: none;
      background-color: #007BFF;
      color: white;
    }
    button:hover {
      background-color: #0056b3;
    }
    #status {
      font-size: 24px;
      margin-top: 20px;
    }
  </style>
</head>
<body>
  <h2>Firebase Relay Dashboard</h2>
  <p id="status">Loading...</p>
  <button onclick="setRelay('ON')">Turn ON</button>
  <button onclick="setRelay('OFF')">Turn OFF</button>

  <script>
    // Your web app's Firebase configuration
    const firebaseConfig = {
      apiKey: "YOUR_API_KEY",
      authDomain: "YOUR_PROJECT_ID.firebaseapp.com",
      databaseURL: "https://YOUR_PROJECT_ID.firebaseio.com",
      projectId: "YOUR_PROJECT_ID",
      storageBucket: "YOUR_PROJECT_ID.appspot.com",
      messagingSenderId: "YOUR_SENDER_ID",
      appId: "YOUR_APP_ID"
    };

    // Initialize Firebase
    firebase.initializeApp(firebaseConfig);
    const db = firebase.database();

    const statusEl = document.getElementById('status');

    function setRelay(state) {
      db.ref("/relay").set(state);
    }

    db.ref("/relay").on("value", snapshot => {
      statusEl.textContent = "Relay is: " + snapshot.val();
    });
  </script>
</body>
</html>
