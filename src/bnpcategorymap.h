#ifndef BNPCATEGORYMAP_H
#define BNPCATEGORYMAP_H

#include <QMap>

static QMap<QString, QString> initNormalizedCategoryMap(){
    QMap<QString, QString> bnp_category_map{
        {"Alimentation, supermarché",               "groceries"},
        {"Musique, livres, films",                  "entertainment"},
        {"Loisirs et sorties - Autres",             "entertainment"},
        {"Divertissements, sorties culturelles",    "entertainment"},
        {"Transports en commun",                    "transport"},
        {"Taxi, VTC",                               "transport"},
        {"Stationnement",                           "transport"},
        {"Restaurants, bars",                       "restaurants"},
        {"Virement émis",                           "transfers"},
        {"Banque - Autres",                         "transfers"},
        {"Achats, shopping",                        "shopping"},
        {"Habillement",                             "shopping"},
        {"Pharmacie",                               "health"},
        {"Autres dépenses à catégoriser",           "uncategorized"},
        {"Autres charges",                          "uncategorized"},
        {"Santé - Autres",                          "health"},
        {"Voyages, vacances",                       "travel"},
        {"Location de véhicule",                    "travel"},
        {"Transports et véhicules - Autres",        "travel"},
        {"Billet d'avion, Billet de train",         "travel"},
        {"Carburant",                               "travel"},
        {"Assurance véhicule",                      "insurance"},
        {"Assurance habitation",                    "insurance"},
        {"?????????",                               "services"},
        {"Téléphone",                               "utilities"},
        {"Internet, TV",                            "utilities"},
        {"Retrait d'espèces",                       "cash"},
        {"Loyer",                                   "rent"},
        {"Frais bancaires",                         "bank fees"},
        {"Sport",                                   "sport"},
        {"Scolarité, études",                       "education"},
        {"Bricolage et jardinage",                  "education"},
        {"Cadeaux",                                 "gifts"},
        {"Taxe d'habitation",                       "taxes"},
        {"Impôts et taxes - Autres",                "taxes"},
        {"Impôt sur le revenu",                     "taxes"},
        {"Taxe foncière",                           "taxes"},
        {"Salaires et revenus d'activité",          "income"},
        {"Virement reçu",                           "income"},
        {"Remboursement",                           "income"},
        {"Autres revenus",                          "income"},
        {"Home",                                    "home"},
        {"Virement interne",                        "internal transfer"},
        {"Epargne",                                 "internal transfer"}};

    QMapIterator<QString, QString> i(bnp_category_map);
    QMap<QString, QString> bnp_category_map_normalized;
    while (i.hasNext()) {
        i.next();
        bnp_category_map_normalized.insert(
            i.key().normalized(QString::NormalizationForm_KD),
            i.value());
    }
    return bnp_category_map_normalized;
}
static QMap<QString, QString> bnp_category_map_normalized = initNormalizedCategoryMap();

#endif // BNPCATEGORYMAP_H
