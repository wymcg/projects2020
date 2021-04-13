const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <style>
      html, body {
        height:100%;
        width:100%;
        margin:0;
      }
      body {
        display:flex;
      }
      div {
        margin:auto;
        text-align: center;
        border-radius: 5px;
      }
      input {
        border-radius: 5px;
        margin: 10px;
        padding: 5px;
        width: 100%
      }
      button {
        border-radius: 5px;
        margin: 10px;
        padding: 5px;
        width: 100%;
      }
    </style>
  <body>
    Logged In As:<span id="LoggedIn">NA</span>
    <div>
      <form>
        <input type="text" name="username" id="username" placeholder="Email"><br>
        <input type="password" name="password" id="password" placeholder="Password"><br>
      </form>
      <button onclick="sendData()">Log In</button> 
    </div>
  </body>
  <script>
    function sendData() {
      var xhttp = new XMLHttpRequest();
      let username = document.getElementById('username').value;
      let password = document.getElementById('password').value;
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("LoggedIn").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "sendData?username="+username+"&password="+password, true);
      xhttp.send();
    }
  </script>
</html>
)=====";
