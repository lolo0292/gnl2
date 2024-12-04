/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:32:14 by lleichtn          #+#    #+#             */
/*   Updated: 2024/12/04 17:31:35 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Vérifie si un saut de ligne ('\n') est présent dans le buffer
int	has_newline(char *buffer)
{
	int i = 0; // Index pour parcourir le buffer
	if (buffer == NULL)
	{
		return (0);
	}
	// Parcourir le buffer jusqu'à la fin ou jusqu'à trouver un '\n'
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

// Lit depuis le descripteur et ajoute les données au buffer
int	read_and_store(int fd, char **buffer)
{
	char temp[BUFFER_SIZE + 1]; // Buffer temporaire pour la lecture
	ssize_t bytes_read;         // Nombre d'octets lus
	char *new_buffer;           // Nouveau buffer après concaténation
	// Lire depuis le descripteur
	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		return (bytes_read); // Retourne le résultat de la lecture (-1, 0 ou >0)
	}
	// Ajouter un caractère nul à la fin du buffer temporaire
	temp[bytes_read] = '\0';
	// Si le buffer principal est vide, initialiser avec les données lues
	if (*buffer == NULL)
	{
		*buffer = strdup(temp);
	}
	else
	{
		// Sinon, concaténer les nouvelles données au buffer existant
		new_buffer = malloc(strlen(*buffer) + bytes_read + 1);
		if (new_buffer == NULL)
		{
			return (-1); // Échec de l'allocation
		}
		strcpy(new_buffer, *buffer);
		strcat(new_buffer, temp);
		free(*buffer);
		*buffer = new_buffer;
	}
	return (bytes_read);
}

// Extrait une ligne du buffer
char	*extract_line(char **buffer)
{
	size_t i = 0;     // Index pour parcourir le buffer
	char *line;       // Ligne extraite
	char *new_buffer; // Nouveau buffer après extraction

	if (*buffer == NULL)
	{
		return (NULL);
	}

	// Trouver la position du saut de ligne ou de la fin du buffer
	while ((*buffer)[i] != '\0' && (*buffer)[i] != '\n')
	{
		i++;
	}

	// Allouer de la mémoire pour la ligne extraite
	line = malloc(i + 2);
	if (line == NULL)
	{
		return (NULL);
	}

	// Copier la ligne, y compris le saut de ligne si présent
	strncpy(line, *buffer, i + ((*buffer)[i] == '\n' ? 1 : 0));
	line[i + ((*buffer)[i] == '\n' ? 1 : 0)] = '\0';

	// Créer un nouveau buffer sans la ligne extraite
	new_buffer = strdup(*buffer + i + ((*buffer)[i] == '\n' ? 1 : 0));
	free(*buffer);
	*buffer = new_buffer;

	return (line);
}