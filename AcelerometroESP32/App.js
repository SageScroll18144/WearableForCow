import React, { useState } from 'react';
import { StyleSheet, Text, View, Button, Alert } from 'react-native';
import axios from 'axios';
import * as FileSystem from 'expo-file-system';
import { Picker } from '@react-native-picker/picker'; // Importação correta do Picker

export default function App() {
  const [accelData, setAccelData] = useState('Aguardando dados...');
  const [selectedClass, setSelectedClass] = useState('classe 1');

  const esp32_ip = "http://192.168.4.1"; // Substitua pelo IP correto
  const accel_route = `${esp32_ip}/device`;

  const fetchAccelData = async () => {
    try {
      const response = await axios.get(accel_route);
      if (response.status === 200) {
        setAccelData(response.data); // Atualiza os dados recebidos
      } else {
        Alert.alert('Erro', `Erro ao acessar a rota: ${response.status}`);
      }
    } catch (error) {
      Alert.alert('Erro', `Erro ao tentar se conectar ao ESP32: ${error}`);
    }
  };

  const downloadCSV = async () => {
    const csvContent = `Dados,Classe\n"${accelData}","${selectedClass}"`;
    const fileUri = FileSystem.documentDirectory + 'dados.csv';
    
    try {
      await FileSystem.writeAsStringAsync(fileUri, csvContent, {
        encoding: FileSystem.EncodingType.UTF8,
      });
      Alert.alert('Sucesso', 'Arquivo CSV baixado com sucesso!');
      console.log('Arquivo salvo em:', fileUri);
    } catch (error) {
      Alert.alert('Erro', 'Falha ao salvar o arquivo CSV');
      console.error(error);
    }
  };

  return (
    <View style={styles.container}>
      <Text style={styles.text}>Dados do Acelerômetro:</Text>
      <Text style={styles.accelData}>{accelData}</Text>
      
      <Text style={styles.text}>Selecione a Classe:</Text>
      <Picker
        selectedValue={selectedClass}
        style={styles.picker}
        onValueChange={(itemValue) => setSelectedClass(itemValue)}
      >
        <Picker.Item label="Classe 1" value="classe 1" />
        <Picker.Item label="Classe 2" value="classe 2" />
        <Picker.Item label="Classe 3" value="classe 3" />
      </Picker>

      <Button title="Obter dados do acelerômetro" onPress={fetchAccelData} />
      <Button title="Baixar CSV" onPress={downloadCSV} />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#fff',
    padding: 20,
  },
  text: {
    fontSize: 18,
    marginVertical: 10,
  },
  accelData: {
    fontSize: 16,
    color: '#333',
    marginBottom: 20,
  },
  picker: {
    height: 50,
    width: 200,
    marginBottom: 20,
  },
});
