/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:18:34 by prigaudi          #+#    #+#             */
/*   Updated: 2025/06/02 19:36:12 by okientzl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include <signal.h>

extern volatile sig_atomic_t g_signal;

void set_signals_interactive(void);
void set_signals_heredoc(void);
void set_signals_child(void);
// ========== SIGNALS ==========
/*void	signals(void);*/
/*void	sigint_act(int signum);*/

// ========== HEREDOC ==========
int		read_line_hook(void);
/*void	sigint_heredoc_handler(int signum);*/

#endif
