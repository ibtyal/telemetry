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
        const response = await fetch("https://siima.tech/sessions"); // Asegúrate de usar tu dominio aquí
        const data = await response.json();
        this.files = data.files;
      } catch (error) {
        console.error("Error al obtener la lista de archivos:", error);
      }
    },
    downloadFile(fileName) {
      const url = `https://siima.tech/download/${fileName}`;
      window.open(url, "_blank"); // Abre la descarga en una nueva ventana o pestaña
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
