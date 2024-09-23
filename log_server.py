import requests

# Defina o endereço IP do ESP32 (substitua pelo IP correto)
esp32_ip = "http://192.168.4.1"

# Defina a rota do acelerômetro
accel_route = esp32_ip + "/device"

try:
    # Faz uma solicitação GET à rota do acelerômetro
    response = requests.get(accel_route)

    # Verifica se a solicitação foi bem-sucedida
    if response.status_code == 200:
        # Imprime o valor retornado pela rota
        print(f"Acelerômetro X: {response.text}")
    else:
        print(f"Erro ao acessar a rota: {response.status_code}")
except requests.exceptions.RequestException as e:
    print(f"Erro ao tentar se conectar ao ESP32: {e}")

