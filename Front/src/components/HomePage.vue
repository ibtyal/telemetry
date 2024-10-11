<template>
  <div class="botones_index">
    <div>
      <img src="../assets/siima_logo_index.png" alt="Logo Siima 2023" />
    </div>
    <div class="botones">
      <div>
        <router-link
          v-if="vehicleActive"
          to="/realtime-data"
          class="boton_datos"
        >
          <div>
            <img src="../assets/RealTimeData.png" alt="Datos en tiempo real" />
          </div>
          <!-- <div class="text_index"><RealTimeData /></div> -->
        </router-link>
        <div v-else class="boton_datos">
          <div><img src="../assets/icon_off.png" alt="OFFLINE :C" /></div>
          <div class="text_index">
            <h2>{{ $t("offline") }}</h2>
          </div>
        </div>
      </div>
      <router-link to="/sessions" class="boton_historial">
        <div><img src="../assets/SessionList.png" alt="Sesiones" /></div>
        <div class="text_index">
          <h2>{{ $t("sessions_registered") }}</h2>
        </div>
      </router-link>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      ws: null,
      vehicleActive: false, // Variable para habilitar el botón
    };
  },
  mounted() {
    this.checkVehicleStatus();
  },
  methods: {
    checkVehicleStatus() {
      // Conectar al WebSocket de /ws-status
      this.ws = new WebSocket("ws://siima.tech/ws-status");

      this.ws.onopen = () => {
        console.log("Conexión WebSocket abierta");
      };

      this.ws.onmessage = (event) => {
        const data = JSON.parse(event.data);
        // Habilitar el botón si se reciben datos
        this.vehicleActive = !!data; // Habilitar el botón si hay datos
      };

      this.ws.onclose = () => {
        console.log("Conexión WebSocket cerrada");
        this.vehicleActive = false; // Deshabilitar el botón cuando se cierre la conexión
      };
    },
  },
};
</script>

<style>
* {
  margin: 0px;
  padding: 0px;
  box-sizing: border-box;
}

body {
  background-image: url(../assets/background.jpg);
  background-repeat: no-repeat;
  background-size: cover;
  align-items: center;
  justify-content: center;
}

h1 {
  font-family: "Kanit", sans-serif;
  font-weight: 600;
  color: white;
}

h2 {
  font-family: "Kanit", sans-serif;
  font-weight: 600;
  color: white;
}

h3 {
  font-family: "Kanit", sans-serif;
  font-weight: 300;
  font-size: 28px;
  color: white;
}

h4 {
  font-family: "Kanit", sans-serif;
  font-weight: 600;
  font-size: 150px;
  color: white;
}

li {
  font-family: "Kanit", sans-serif;
  font-weight: 300;
  color: white;
  font-size: 27px;
}

/* Index Styles */

.contenedor_index {
  display: flex;
  justify-content: center;
  align-items: center;
  height: 64vh;
}

.botones_index {
  width: 900px;
  height: 400px;
  text-align: center;
  justify-content: center;
}

.botones {
  display: flex;
  width: auto;
  height: auto;
  padding: 10px;
  text-align: center;
}

.text_index {
  margin-left: 20px;
}

.boton_datos {
  display: flex;
  align-items: center;
  float: left;
  width: 400px;
  height: auto;
  background-color: rgba(5, 13, 27, 0.836);
  border-radius: 20px;
  padding: 20px;
  margin-left: 10px;
  align-items: center;
  justify-content: center;
  transition: background-color 0.5s ease;
}

.boton_datos:hover {
  display: flex;
  align-items: center;
  float: left;
  width: 400px;
  height: auto;
  background-color: rgba(26, 83, 17, 0.836);
  border-radius: 20px;
  padding: 20px;
  margin-left: 10px;
  align-items: center;
  justify-content: center;
  cursor: pointer;
}

.boton_historial {
  display: flex;
  align-items: center;
  float: left;
  width: 400px;
  height: auto;
  background-color: rgba(5, 13, 27, 0.836);
  border-radius: 20px;
  padding: 20px;
  margin-left: 10px;
  align-items: center;
  justify-content: center;
  transition: background-color 0.5s ease;
}

.boton_historial:hover {
  display: flex;
  align-items: center;
  float: left;
  width: 400px;
  height: auto;
  background-color: rgba(26, 83, 17, 0.836);
  border-radius: 20px;
  padding: 20px;
  margin-left: 10px;
  align-items: center;
  justify-content: center;
  cursor: pointer;
}
/* End of Index Styles */
/* HEADER Styles */
header {
  background-color: rgba(5, 13, 27, 0.836);
  color: #fff;
  padding: 5px;
  width: 100%;
  height: 100px;
}

.logo {
  display: inline-block;
  margin-right: 20px;
  margin-left: 20px;
  margin-top: 20px;
  vertical-align: middle;
}

.menu {
  float: right;
  margin-top: 20px;
}

.menu ul {
  list-style: none;
}

.menu ul li {
  vertical-align: middle;
  display: inline-block;
  margin-right: 10px;
}

.menu ul li a {
  text-decoration: none;
  color: #fff;
  border-radius: 5px;
  padding: 0px 20px 0px 20px;
  transition: background-color 0.5s ease;
}

.menu ul li a:hover {
  text-decoration: none;
  color: #ffffff;
  background-color: #87ba47;
  border-radius: 5px;
  padding: 10px 20px 30px 20px;
}

ul > li > a > img {
  max-height: 25px;
}
/* End of HEADER Styles */

/*the container must be positioned relative:*/
.lang-select {
  display: flex;
  float: right;
}

.spotify {
  display: flex;
  width: 450px;
  height: auto;
  background-color: transparent;
  border-radius: 12px;
  border: 0px;
  border-color: transparent;
}

footer {
  display: flex;
  height: auto;
  align-items: center;
  background-color: rgba(5, 13, 27, 0.836);
  text-align: center;
  color: white;
  border-radius: 20px;
  justify-content: center;
  font-family: "Kanit", sans-serif;
  color: white;
  font-size: 18px;
}
</style>
