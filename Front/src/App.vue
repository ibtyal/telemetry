<template>
  <header>
    <div class="menu">
      <ul>
        <li>
          <a href="/"><img src="./assets/icon_home_small.png" alt="Home" /></a>
        </li>
      </ul>
    </div>
    <div class="lang-select">
      <select v-model="locale" @change="changeLocale">
        <option value="en">English 🇬🇧</option>
        <option value="es">Español 🇪🇸</option>
        <option value="de">Deutsch 🇩🇪</option>
        <option value="zh">中文 🇨🇳</option>
      </select>
    </div>
  </header>
  <body>
    <div class="contenedor_index">
      <RouterView />
    </div>
    <div>
      <iframe
        class="spotify"
        src="https://open.spotify.com/embed/episode/1wlmCEpgKFApRTiVX7MdRj?utm_source=generator"
        allow="autoplay; clipboard-write; encrypted-media; fullscreen; picture-in-picture"
        loading="lazy"
      ></iframe>
    </div>
  </body>
  <footer>
    <p>
      Unidades Tecnológicas de Santander || Ingeniería Electromecánica <br />
      Jonathan Fabian Polo Godoy ||
      <a href="mailto:jonathan.polo@pm.me"
        ><img
          src="./assets/email.png"
          alt="Emial Jonathan Polo"
          style="height: 56.25%"
      /></a>
      <a href="https://www.instagram.com/semillerosiima/"
        ><img
          src="./assets/instagram.png"
          alt="Instagram Siima"
          style="height: 56.25%"
      /></a>
      <a href="https://www.facebook.com/semilleroSIIMA2019"
        ><img
          src="./assets/facebook.png"
          alt="Facebook Siima"
          style="height: 56.25%; color: white" /></a
      >|| <span style="font-family: 'MedievalSharp', regular">L.V.X.</span>
      <br />
      2023
    </p>
  </footer>
</template>

<script>
const wsstatus = import.meta.env.VITE_WS;
export default {
  data() {
    return {
      locale: "es", // Idioma predeterminado
    };
  },
  methods: {
    changeLocale() {
      this.$i18n.locale = this.locale; // Cambia el idioma
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
  background-image: url(./assets/background.jpg);
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
  font-weight: 100;
  font-size: 70px;
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
  height: 78vh;
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
  padding: 2px;
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
  margin-top: 10px;
}

.menu ul {
  list-style: none;
  display: flex;
  float: left;
  margin-right: 50%;
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
