#include <global.h>
#include <checkArgs.hpp>
#include <thread>
#include <vector>
#include <time.h>
#include <stdlib.h>

uint64_t *Array = nullptr;
uint32_t sum = 0;
uint32_t sumTotalParalelo;
uint32_t *vRandom = nullptr;
uint64_t *ArregloMa = nullptr;
bool verbosidad;

void sumaParcial(size_t start, size_t end, uint32_t sum, size_t j)
{
	for (size_t i = start; i < end; ++i)
	{
		ArregloMa[j] += Array[i];
		//std::cout << "valor: " << sum << std::endl;
	}
}

void Llenado(size_t start, size_t end)
{
	for (auto i = start; i < end; ++i)
	{
		Array[i] = vRandom[i];
	}
}

int main(int argc, char **argv)
{
	uint64_t totalElementos;
	uint32_t numThreads;
	uint64_t l_inferior;
	uint64_t l_superior;
	uint32_t suma_Serial = 0;
	uint32_t sum;

	auto argumentos = (std::shared_ptr<checkArgs>)new checkArgs(argc, argv);

	totalElementos = argumentos->getArgs().tamProblema;
	numThreads = argumentos->getArgs().numThreads;
	l_inferior = argumentos->getArgs().l_inf;
	l_superior = argumentos->getArgs().l_sup;
	verbosidad = argumentos->getArgs().verbosidad;

	if(verbosidad){
	std::cout << "Elementos: " << totalElementos << std::endl;
	std::cout << "Threads  : " << numThreads << std::endl;
	std::cout << "Límite inferior rango aleatorio : " << l_inferior << std::endl;
	std::cout << "Límite superior rango aleatorio : " << l_superior << std::endl;
	}
	std::vector<std::thread *> llenado_thread;
	std::vector<std::thread *> sumaP_thread;
	std::vector<uint32_t> llenado_Serial;

	Array = new uint64_t[totalElementos];
	vRandom = new uint32_t[totalElementos];
	ArregloMa = new uint64_t[numThreads];

	// ----- Llenar arreglo con random ---- //

	std::random_device deviceV;
	std::mt19937 rngV(deviceV());
	std::uniform_int_distribution<uint32_t> nArregloRandom(l_inferior, l_superior);

	for(size_t i=0; i < totalElementos; ++i){
		uint32_t number = nArregloRandom(rngV);
		vRandom[i]= number;
		//std::cout << "Numero random:  " << number << std::endl;
	}

	//-----------------------------------------Primer Módulo-----------------------------------------//

			// -- Llenado paralelo -- //

	for (uint32_t i = 0; i < numThreads; ++i)
	{
		llenado_thread.push_back(new std::thread(Llenado,
												 i * (totalElementos) / numThreads,
												 (i + 1) * (totalElementos) / numThreads
												 ));
	}

	auto start = std::chrono::system_clock::now();

	for (auto &th : llenado_thread)
	{
		th->join();
	}

	auto end     = std::chrono::high_resolution_clock::now(); 
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto TotalTimeParallelFilling = elapsed.count();

			// -- Llenado serial -- //

	start = std::chrono::system_clock::now();

	for (size_t i = 0; i < totalElementos; i++)
	{

		llenado_Serial.push_back(vRandom[i]);

	}

	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto TotalTimeSerialFilling = elapsed.count();

	//-----------------------------------------Segundo Módulo-----------------------------------------//
	
			// -- Suma paralelo -- //

	for (size_t j = 0; j < numThreads; ++j)
	{
		sumaP_thread.push_back(new std::thread(sumaParcial,
											   j * (totalElementos) / numThreads,
											   (j + 1) * (totalElementos) / numThreads,
											   sum,
											   j));
	}

	start = std::chrono::system_clock::now();  

	for (auto &th : sumaP_thread)
	{
		th->join();
	}
	//Consolidación//
	for(size_t k = 0; k < numThreads;++k){
		sum +=ArregloMa[k];
	}
	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto TotalTimeParallelSum = elapsed.count();

	// -- Suma Serial -- //

	start = std::chrono::system_clock::now();

	for (size_t i = 0; i < totalElementos; ++i)
	{
		suma_Serial += llenado_Serial[i];
	}

	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto TotalTimeSerialSum = elapsed.count();

	float speedUpF = (TotalTimeSerialFilling/TotalTimeParallelFilling);
  	float eficienciadF = 1/(1+(TotalTimeParallelFilling/TotalTimeSerialFilling));

	float speedUp = (TotalTimeSerialSum/TotalTimeParallelSum);
  	float eficiencia = 1/(1+(TotalTimeParallelSum/TotalTimeSerialSum));

	// -- Resultados -- //
	if(verbosidad){
	std::cout << "======Resultados======" << std::endl;
	std::cout << "La suma Total secuencial: " << suma_Serial << std::endl;
	std::cout << "La suma Total thread: " << sum << std::endl;
	}
	std::cout << "====Llenado arreglo====" << std::endl;
	std::cout << "Tiempo Threads		: " << TotalTimeParallelFilling << "[ms]" << std::endl;
	std::cout << "Tiempo secuencial 	: " << TotalTimeSerialFilling << "[ms]" <<std::endl;
	std::cout << "====Suma valores====" << std::endl;
	std::cout << "Tiempo threads		: " <<  TotalTimeParallelSum << "[ms]" << std::endl;
	std::cout << "Tiempo secuencial 	: " <<  TotalTimeSerialSum << "[ms]" << std::endl;
	std::cout << "====Desempeño====" << std::endl;
	std::cout << "SpeedUp Llenado : " << speedUpF << "[ms/ms]" <<std::endl;
	std::cout << "Eficiencia Llenado : " << eficienciadF << "[1/ms]" <<std::endl;
	std::cout << "SpeedUp Suma : " << speedUp << "[ms/ms]" <<std::endl;
	std::cout << "Eficiencia Suma : " << eficiencia << "[1/ms]" <<std::endl;

	return (EXIT_SUCCESS);
}
