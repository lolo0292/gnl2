/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:31:59 by lleichtn          #+#    #+#             */
/*   Updated: 2024/12/04 17:33:23 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Fonction principale pour lire une ligne depuis un descripteur de fichier
char	*get_next_line(int fd)
{
	static char	*buffer = NULL;

	// Stockage persistant du buffer entre les appels
	char *line = NULL;     // Ligne à retourner
	int newline_found = 0; // Indique si un saut de ligne est trouvé
	int read_result = 1;   // Résultat de la lecture
	// Vérifier si le descripteur de fichier est valide et si la taille du buffer est correcte
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	// Lire jusqu'à ce qu'un saut de ligne soit trouvé ou que la lecture soit terminée
	while (newline_found == 0 && read_result > 0)
	{
		read_result = read_and_store(fd, &buffer);
		newline_found = has_newline(buffer);
	}
	// Extraire une ligne du buffer
	line = extract_line(&buffer);
	// Si aucune ligne n'est extraite, libérer le buffer et retourner NULL
	if (line == NULL || *line == ' ')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (line);
}
