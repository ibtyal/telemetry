<template>
  <div>
    <h2>{{ $t("sessions_registered") }}</h2>
  </div>
  <div class="historial">
    <ul>
      <li v-for="file in files" :key="file">
        <span>{{ file }}</span>
        <button @click="downloadFile(file)">Download</button>
      </li>
    </ul>
  </div>
</template>

<script>
export default {
  data() {
    return {
      files: [],
    };
  },
  created() {
    this.fetchFiles();
  },
  methods: {
    async fetchFiles() {
      try {
        console.log("Iniciando solicitud a:", "https://siima.tech/sessions"); // Log de la URL

        const response = await fetch("https://siima.tech/sessions");

        console.log("Estado de la respuesta:", response.status); // Log del código de estado HTTP
        console.log("Tipo de contenido:", response.headers.get("content-type")); // Verifica el tipo de contenido

        // Asegúrate de que el tipo de contenido sea JSON antes de intentar parsear
        if (
          response.headers.get("content-type")?.includes("application/json")
        ) {
          const data = await response.json();
          console.log("Datos recibidos:", data); // Log de los datos obtenidos
          this.files = data.files;
        } else {
          throw new Error("El contenido no es JSON");
        }
      } catch (error) {
        console.error("Error al obtener la lista de archivos:", error);
      }
    },
    downloadFile(fileName) {
      const url = `https://siima.tech/download/${fileName}`;
      console.log("Descargando archivo desde:", url); // Log de la URL de descarga
      window.open(url, "_blank");
    },
  },
};
</script>

<style>
.historial {
  background-color: rgba(5, 13, 27, 0.836);
  width: 70%;
  height: auto;
  margin-top: 20px;
  margin-left: 5%;
  padding: 20px;
  border-radius: 10px;
  align-items: center;
}
.historial ul {
  height: 450px;
  width: auto;
  overflow-y: auto;
}

.historial ul li {
  list-style: none;
  text-decoration: none;
}
</style>
