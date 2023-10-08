/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_comentado.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:35:17 by davgalle          #+#    #+#             */
/*   Updated: 2023/10/08 15:13:48 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024 // Define un tamaño de búfer para las lecturas del archivo
/*
int	count_lines(fd)
{
	static int	i; // Variable estática para contar líneas
	char		buffer; // Variable para leer caracteres del archivo
	ssize_t		bytes_read; // Variable para el número de bytes leídos

	buffer = '\0'; // Inicializa buffer con '\0' (nulo)
	i = 0; // Inicializa i con 0
	if (i == 0) // Comprueba si i es igual a 0
	{
		while ((bytes_read = read(fd, &buffer, 1)) > 0)
		{
			if (buffer == '\n') // Si se encuentra un carácter de nueva línea
				i++; // Incrementa el contador de líneas
		}
	}
	if (buffer != '\n' && i > 0) // Si el último carácter leído no es nueva línea y se encontró al menos una línea
		i++; // Incrementa el contador de líneas
	return (i); // Devuelve el contador de líneas
}
*/
char	*get_next_line(int fd)
{
	char	*line; // Puntero para almacenar la línea leída
	char	*new_line; // Puntero para realocar memoria
	char	buffer; // Variable para leer caracteres del archivo
	int		i; // Contador para la posición en la línea
	ssize_t	bytes_read; // Variable para el número de bytes leídos

	buffer = '\0'; // Inicializa buffer con '\0'
	line = NULL; // Inicializa el puntero line como NULL
	i = 0; // Inicializa i con 0
	while ((bytes_read = read(fd, &buffer, 1)) > 0)
	{
		if (buffer == '\n') // Si se encuentra un carácter de nueva línea
			break ; // Sal del bucle
		new_line = malloc(i + 2); // Realoca memoria para la línea con espacio adicional
		if (!new_line) // Si no se pudo realocar la memoria
			return (NULL); // Devuelve NULL para indicar un error
		if (line)
        {
            memcpy(new_line, line, i); // Usar memcpy para copiar los caracteres anteriores
            free(line); // Liberar memoria anterior si estaba asignada
        }
		line = new_line; // Actualiza el puntero line
		line[i] = buffer;
        i++; // Almacena el carácter en la línea
	}
	if (bytes_read == 0 && i == 0) // Si llegamos al final del archivo y no se leyó nada
	{
		free(line); // Libera la memoria asignada a line (que aún es NULL)
		return (NULL); // Devuelve NULL para indicar el final del archivo
	}
	line[i] = '\0'; // Agrega el carácter nulo al final de la línea
	return (line); // Devuelve la línea leída
}

int	main(void)
{
	int	fd; // Descriptor de archivo

	fd = open("archivo.txt", O_RDONLY); // Abre el archivo "archivo.txt" para lectura

	char *line; // Puntero para almacenar las líneas leídas

	while ((line = get_next_line(fd)) != NULL) // Mientras se puedan leer líneas
	{
		printf("%s\n", line); // Imprime la línea
		free(line); // Libera la memoria asignada a la línea
	}
	close(fd); // Cierra el archivo
	return (0); // Retorna 0 para indicar que el programa se ejecutó correctamente
}
