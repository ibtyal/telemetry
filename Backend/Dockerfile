# Utiliza una imagen base de Python 3.12
FROM python:3.12-slim

# Establece el directorio de trabajo
WORKDIR /app

# Copia el archivo de requisitos en el directorio de trabajo
COPY . .

# Instala las dependencias
RUN pip install --no-cache-dir -r requirements.txt

# Expone el puerto que utilizará Streamlit
EXPOSE 8000

# Start command
CMD [ "uvicorn","main:app","--reload"]
