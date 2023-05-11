setwd("C:/Users/Julia/Documents/GitHub/abm_dengue/data_cluster_3/")
library(dplyr)
library(ggplot2)
library(sf)
### CASES OBSERVED #####
sectores_dem <- st_read("C:/Users/Julia/OneDrive - Universidad de los Andes/Maestría/Tesis/CasesPerLevel/Demographic/demographic_sectores.shp")
sectores_cases <- st_drop_geometry(sectores_dem)
all_cases_n_s <- sectores_cases %>% group_by(YEAR, MONTH) %>% summarise(CASES_SUM = sum(CASES)) %>%
  select(YEAR, MONTH, CASES_SUM)
all_cases_2013 <- all_cases_n_s[all_cases_n_s$YEAR == 2013,]
cases_2013 <- as.integer(all_cases_2013$CASES_SUM*(0.05)/0.2)

DAY <- seq(0,359)
data_frame <- data.frame(DAY)

for(i in 1:10){
  if(i != 12){
  path <- paste0("out_",toString(i),".csv")
  temp_sf <- read.csv(path, header = F, sep = ",")
  temp_sf <- temp_sf[,-c(1,5)]
  colnames(temp_sf) <- c("S", "I", "R")
  temp_sf$lag_I <- c(0,temp_sf[-c(360),"I"])
  temp_sf$lag_R <- c(0,temp_sf[-c(360),"R"])
  temp_sf$daily <- temp_sf$I-temp_sf$lag_I+temp_sf$R-temp_sf$lag_R
  
  data_frame[,paste0("M_",i)] <-  temp_sf$daily
  }
}

months <- c(0, 
            rep(1, times = 31),
            rep(2, times = 28),
            rep(3, times = 31),
            rep(4, times = 30),
            rep(5, times = 31),
            rep(6, times = 30),
            rep(7, times = 31),
            rep(8, times = 31),
            rep(9, times = 30),
            rep(10, times = 31),
            rep(11, times = 30),
            rep(12, times = 25))
data_frame$MONTH <- months

data_frame_monthly <- data_frame %>% 
  group_by(MONTH) %>% 
  summarise(M_1 = sum(M_1),
             M_2 = sum(M_2),
             M_3 = sum(M_3),
             M_4 = sum(M_4),
             M_5 = sum(M_5),
             M_6 = sum(M_6),
             M_7 = sum(M_7),
             M_8 = sum(M_8),
             M_9 = sum(M_9),
             M_10 = sum(M_10))%>%
            # M_10 = sum(M_11),
            # M_10 = sum(M_12),
            # M_10 = sum(M_13),
            # M_10 = sum(M_14),
            # M_10 = sum(M_15),
            # M_10 = sum(M_16),
            # M_10 = sum(M_17),
            # M_10 = sum(M_18),
            # M_10 = sum(M_19),
            # M_10 = sum(M_20)) %>%
  filter(MONTH > 0) %>%
  select(-c(MONTH))

monthly_stats <- data_frame_monthly %>%
  rowwise() %>%
  mutate(mean = as.integer(mean(c_across(where(is.numeric)), na.rm=TRUE)),
         low = mean + as.integer(sd(c_across(where(is.numeric)), na.rm=TRUE)),
         high = mean - as.integer(sd(c_across(where(is.numeric)), na.rm=TRUE)))

monthly_stats <- monthly_stats %>% select(low, mean, high)
monthly_stats$MONTH <- c(1,2,3,4,5,6,7,8,9,10,11,12)
monthly_stats$OBSERVED = cases_2013

# Plot the line plot
ggplot(monthly_stats, aes(x = MONTH)) + 
  geom_line(aes(y = OBSERVED, color = "OBSERVED"), size = 0.8)+
  geom_line(aes(y = mean, color = "SIMULATED"), size = 0.8)+
  geom_line(aes(y = low), color = "black", linetype = "dashed", size = 0.5)+
  geom_line(aes(y = high), color = "black", linetype = "dashed", size = 0.5)+
  theme_bw()+
  ylab("DENV CASES")+
  xlab("MONTH")+
  scale_color_manual(name = "", values = c("OBSERVED" = "#3F5151", "SIMULATED" = "#A42820"))+
  theme(legend.position = "bottom",
        legend.title = element_blank())


monthly_stats <- data_frame_monthly %>%
  rowwise() %>%
  mutate(median = as.integer(median(c_across(where(is.numeric)), na.rm=TRUE)),
         low_q = as.integer(quantile(c_across(where(is.numeric)), na.rm=TRUE)[2]),
         high_q = as.integer(quantile(c_across(where(is.numeric)), na.rm=TRUE)[4]))

monthly_stats <- monthly_stats %>% select(low_q, median, high_q)
monthly_stats$MONTH <- c(1,2,3,4,5,6,7,8,9,10,11,12)
monthly_stats$OBSERVED = cases_2013

# Plot the line plot
ggplot(monthly_stats, aes(x = MONTH)) + 
  geom_line(aes(y = OBSERVED, color = "OBSERVED"), size = 0.8)+
  geom_line(aes(y = median, color = "SIMULATED"), size = 0.8)+
  geom_line(aes(y = low_q), color = "black", linetype = "dashed", size = 0.5)+
  geom_line(aes(y = high_q), color = "black", linetype = "dashed", size = 0.5)+
  theme_bw()+
  ylab("DENV CASES")+
  xlab("MONTH")+
  scale_color_manual(name = "", values = c("OBSERVED" = "#3F5151", "SIMULATED" = "#A42820"))+
  theme(legend.position = "bottom",
        legend.title = element_blank())
